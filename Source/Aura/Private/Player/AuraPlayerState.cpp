// Copyright Richard Skala

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

#include "Player/AuraPlayerState.h"

AAuraPlayerState::AAuraPlayerState()
{
	// How often per second the server will try to update clients
	NetUpdateFrequency = 100.0f;

	// Create the Ability System Component for this enemy
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");

	// Ensure the ASC is replicated
	AbilitySystemComponent->SetIsReplicated(true);

	// Construct the Attribute Set 
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
