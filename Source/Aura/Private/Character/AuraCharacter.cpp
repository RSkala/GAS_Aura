// Copyright Richard Skala


#include "Character/AuraCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

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
