// Copyright Richard Skala

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAuraPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	void Move(const struct FInputActionValue& InputActionValue);

private:
	UPROPERTY(EditAnywhere, Category  = "Input")
	TObjectPtr<class UInputMappingContext> AuraInputMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> AuraMoveInputAction;
};
