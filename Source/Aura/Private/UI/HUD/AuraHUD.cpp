// Copyright Richard Skala

#include "UI/HUD/AuraHUD.h"

#include "UI/Widget/AuraUserWidget.h"

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* NewWidget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	NewWidget->AddToViewport();
}
