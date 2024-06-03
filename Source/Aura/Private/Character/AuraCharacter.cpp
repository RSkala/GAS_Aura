// Copyright Richard Skala


#include "Character/AuraCharacter.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerState.h"

AAuraCharacter::AAuraCharacter()
{
	// Get the Character Movement Component from this Character
	UCharacterMovementComponent* CharacterMovementComponent = GetCharacterMovement();
	check(CharacterMovementComponent);

	// Orient the player character's direction to the movement direction
	CharacterMovementComponent->bOrientRotationToMovement = true;

	// Set the rotation movement rate
	CharacterMovementComponent->RotationRate = FRotator(0.0f, 400.0f, 0.0f); // This should be configurable in the Blueprint, but give it a default value

	// Constrain movement to a plane
	CharacterMovementComponent->bConstrainToPlane = true;

	// Snap the player character to a plane
	CharacterMovementComponent->bSnapToPlaneAtStart = true;

	// The character itself should not use the controller's rotation
	bUseControllerRotationRoll = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Initialize the Ability Actor Info on the AuraPlayerState's AbilitySystemComponent (FOR THE CLIENT ONLY)
	InitAbilityActorInfo();
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Initialize the Ability Actor Info on the AuraPlayerState's AbilitySystemComponent (FOR THE SERVER ONLY)
	InitAbilityActorInfo();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	// For player characters, the AbilitySystemComponent and Attribute set are on the PlayerState
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);

	// Set the AAuraCharacterBase ability system variables from the player state
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();

	check(AbilitySystemComponent);

	// Initialize the ability actor info with the PlayerState as the OwnerActor and this AuraCharacter as the AvatarActor 
	AbilitySystemComponent->InitAbilityActorInfo(AuraPlayerState, this);

	/*
	UAbilitySystemComponent* PlayerStateAbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	check(PlayerStateAbilitySystemComponent);
	PlayerStateAbilitySystemComponent->InitAbilityActorInfo(AuraPlayerState, this);

	AbilitySystemComponent = PlayerStateAbilitySystemComponent;
	AttributeSet = AuraPlayerState->GetAttributeSet();
	*/
}
