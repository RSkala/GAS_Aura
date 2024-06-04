// Copyright Richard Skala


#include "Player/AuraPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Interaction/EnemyInterface.h"

DEFINE_LOG_CATEGORY_STATIC(LogAuraPlayerController, Log, All)

AAuraPlayerController::AAuraPlayerController()
{
	UE_LOG(LogAuraPlayerController, Log, TEXT("AAuraPlayerController::AAuraPlayerController - %s"), *GetName());

	// Ensure this player controller is replicated (sent from server to all clients)
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	//UE_LOG(LogAuraPlayerController, Log, TEXT("AAuraPlayerController::PlayerTick - %s"), *GetName());
	Super::PlayerTick(DeltaTime);
	
	// Perform trace here
	CursorTrace();
}

void AAuraPlayerController::BeginPlay()
{
	UE_LOG(LogAuraPlayerController, Log, TEXT("AAuraPlayerController::BeginPlay - %s"), *GetName());

	Super::BeginPlay();

	// Assert if the Input Mapping Context has not been set. This should have been set up in the Blueprint.
	check(AuraInputMappingContext);

	// Add Input Mapping Context
	// * Note: We can check the Input Component class in: Edit->Project Settings->Engine->Input->Default Classes->Default Input Component Class
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	//check(Subsystem); // Note: We do not want a "check" here as we will not get a valid subsystem unless we are on the locally controlled machine
	if (Subsystem != nullptr)
	{
		Subsystem->AddMappingContext(AuraInputMappingContext, 0); // We only have one InputMappingContext, so just set the priority to 0.
	}

	// Set various Player Controller mouse / mouse cursor settings
	bShowMouseCursor = true; // Set the mouse cursor to be visible
	DefaultMouseCursor = EMouseCursor::Default; // Use default mouse cursor

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); // Do not lock mouse to viewport
	InputModeData.SetHideCursorDuringCapture(false); // When the cursor is "captured" in the viewport, do not hide the cursor
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	UE_LOG(LogAuraPlayerController, Log, TEXT("AAuraPlayerController::SetupInputComponent - %s"), *GetName());

	Super::SetupInputComponent();

	// Get the EnhancedInputComponent so we can bind input mappings to it
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	// Bind the "Move" input action to the Move function
	EnhancedInputComponent->BindAction(AuraMoveInputAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	//UE_LOG(LogAuraPlayerController, Log, TEXT("AAuraPlayerController::Move - InputAxisVector: %s"), *InputAxisVector.ToString());

	// First, figure out which direction is "forward" for the Character

	// Get the Rotation of this Controller
	// If we zero out the Roll (X-angle) and the Pitch (Y-angle), then we have the Yaw value (Z-angle, i.e. rotation around the Z (world-up) axis)
	// If we convert that yaw to a vector, then we essentially have the forward direction

	const FRotator CurrentControlRotation = GetControlRotation(); // GetControlRotation gives you the control rotation in world space 
	const FRotator YawRotation(0.0f, CurrentControlRotation.Yaw, 0.0f); // FORCEINLINE TRotator(T InPitch, T InYaw, T InRoll);
	
	// Now we have a rotation with which to get a foward vector from

	// Get the player character's forward direction from the player character's current rotation
	// This "forward direction" is the vector pointing from the camera to the character, leveled out (parallel to the ground)
	// * TODO: Read more about the Control Rotation
	const FRotationMatrix RotationMatrix = FRotationMatrix(YawRotation);
	const FVector ForwardDirection = RotationMatrix.GetUnitAxis(EAxis::X); // X-axis is the Forward direction vector in Unreal Engine. GetUnitAxis returns a normalized vector.
	const FVector RightDirection = RotationMatrix.GetUnitAxis(EAxis::Y);   // Y-axis is the Right direction vector in Unreal Engine. GetUnitAxis returns a normalized vector.

	// Check if the controlled pawn is valid before using, as Move is called every frame and might be called before the Pawn is valid
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		// Handle forward/back movement so use ForwardDirection and use the Y value of the movement input for the scale [-1..1]
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);

		// Handle left/right movement so use RightDirection and use the X value of the movement input for the scale [-1..1]
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AAuraPlayerController::CursorTrace()
{
	//UE_LOG(LogAuraPlayerController, Log, TEXT("AAuraPlayerController::CursorTrace - %s"), *GetName());

	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit)
	{
		return;
	}

	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor(); // No need for a Cast here because of TScriptInterface

	// Line trace from cursor. There are several scenarios:
	// * A. LastActor is null && ThisActor is null
	//   - This means we are not highlighting anything valid and also did not in the previous frame
	//   - Do nothing
	// * B. LastActor is null && ThisActor is valid
	//   - This means that we were NOT highlighting ThisActor in the previous frame
	//   - Highlight ThisActor
	// * C. LastActor is valid && ThisActor is null
	//   - This means we hovered over an IEnemyInterface last frame and in this frame we are no longer highlighting it
	//   - Unhighlight LastActor
	// * D. Both actors are valid, but LastActor != ThisActor
	//   - This means Hovering over one enemy and now highlighting a different enemy
	//   - Unhighlight LastActor and Highlight ThisActor
	// * E. Both actors are valid, but LastActor == ThisActor
	//   - This means we are still highlighting the same actor
	//   - Do nothing

	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			// Case B
			ThisActor->HighlightActor();
		}
		else
		{
			// Case A - Both are null, do nothing
		}
	}
	else // LastActor is valid
	{
		if (ThisActor == nullptr)
		{
			// Case C
			LastActor->UnhighlightActor();
		}
		else // Both actors are valid
		{
			if (LastActor != ThisActor)
			{
				// Case D
				LastActor->UnhighlightActor();
				ThisActor->HighlightActor();
			}
			else
			{
				// Case E - Do nothing
			}
		}
	}
}
