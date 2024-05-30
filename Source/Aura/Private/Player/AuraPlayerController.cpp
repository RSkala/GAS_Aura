// Copyright Richard Skala


#include "Player/AuraPlayerController.h"

#include "EnhancedInputSubsystems.h"

DEFINE_LOG_CATEGORY_STATIC(LogAuraPlayerController, Log, All)

AAuraPlayerController::AAuraPlayerController()
{
	UE_LOG(LogAuraPlayerController, Log, TEXT("AAuraPlayerController::AAuraPlayerController - %s"), *GetName());

	// Ensure this player controller is replicated (sent from server to all clients)
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	UE_LOG(LogAuraPlayerController, Log, TEXT("AAuraPlayerController::BeginPlay - %s"), *GetName());

	Super::BeginPlay();

	// Assert if the Input Mapping Context has not been set. This should have been set up in the Blueprint.
	check(AuraInputMappingContext);

	// Add Input Mapping Context
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(AuraInputMappingContext, 0); // We only have one InputMappingContext, so just set the priority to 0.

	// Set various Player Controller mouse / mouse cursor settings
	bShowMouseCursor = true; // Set the mouse cursor to be visible
	DefaultMouseCursor = EMouseCursor::Default; // Use default mouse cursor

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); // Do not lock mouse to viewport
	InputModeData.SetHideCursorDuringCapture(false); // When the cursor is "captured" in the viewport, do not hide the cursor
	SetInputMode(InputModeData);
}
