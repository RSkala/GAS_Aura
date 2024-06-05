// Copyright Richard Skala


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"

DEFINE_LOG_CATEGORY_STATIC(LogOverlayWidgetController, Log, All)

void UOverlayWidgetController::BroadcastInitialValues()
{
	UE_LOG(LogOverlayWidgetController, Log, TEXT("UOverlayWidgetController::BroadcastInitialValues - %s"), *GetName());

	// Get the aura attribute set
	const UAuraAttributeSet* const AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	// Broadcast the real value of attributes
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());

	//AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddUObject
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	UE_LOG(LogOverlayWidgetController, Log, TEXT("UOverlayWidgetController::BindCallbacksToDependencies - %s"), *GetName());

	const UAuraAttributeSet* const AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& AttributeChangeData) const
{
	UE_LOG(LogOverlayWidgetController, Log, TEXT("UOverlayWidgetController::HealthChanged - %s"), *GetName());
	OnHealthChanged.Broadcast(AttributeChangeData.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& AttributeChangeData) const
{
	UE_LOG(LogOverlayWidgetController, Log, TEXT("UOverlayWidgetController::MaxHealthChanged - %s"), *GetName());
	OnMaxHealthChanged.Broadcast(AttributeChangeData.NewValue);
}
