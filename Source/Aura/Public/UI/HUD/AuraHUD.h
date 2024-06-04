// Copyright Richard Skala

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()

public:
	class UOverlayWidgetController* GetOverlayWidgetController(const struct FWidgetControllerParams& WidgetControllerParams);
	void InitOverlay(
		APlayerController* InPlayerController,
		APlayerState* InPlayerState,
		class UAbilitySystemComponent* InAbilitySystemComponent,
		class UAttributeSet* InAuraAttributeSet);

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<class UAuraUserWidget> OverlayWidget;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UAuraUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<class UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UOverlayWidgetController> OverlayWidgetControllerClass;
};
