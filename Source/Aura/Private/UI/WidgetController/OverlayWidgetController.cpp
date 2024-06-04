// Copyright Richard Skala


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	// Get the aura attribute set
	const UAuraAttributeSet* const AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	// Broadcast the real value of attributes
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
}
