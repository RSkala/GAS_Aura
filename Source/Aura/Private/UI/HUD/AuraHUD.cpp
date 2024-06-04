// Copyright Richard Skala

#include "UI/HUD/AuraHUD.h"

#include "UI/Widget/AuraUserWidget.h"
//#include "UI/WidgetController/AuraWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WidgetControllerParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WidgetControllerParams);
	}
	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(
	APlayerController* InPlayerController,
	APlayerState* InPlayerState,
	UAbilitySystemComponent* InAbilitySystemComponent,
	UAttributeSet* InAuraAttributeSet)
{
	// construct WidgetController, construct the widget, set the widget's widgetcontroller , then add to viewport

	// Ensure the class variables are set before creating the overlay widget and overlay widgetcontroller
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class unitialized. Fill out BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class unitialized. Fill out BP_AuraHUD"));

	// Create the overlay widget
	OverlayWidget = CreateWidget<UAuraUserWidget>(GetWorld(), OverlayWidgetClass);

	// Initialize the widget controller params with the incoming values
	const FWidgetControllerParams WidgetControllerParams(InPlayerController, InPlayerState, InAbilitySystemComponent, InAuraAttributeSet);

	// Get the overlay widget controller so we can set it in the overlay widget
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
	OverlayWidget->SetWidgetController(WidgetController);

	// Add the overlay widget to the viewport
	OverlayWidget->AddToViewport();
}

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();
}

