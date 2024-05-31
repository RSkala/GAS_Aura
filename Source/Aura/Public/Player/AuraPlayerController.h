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
	virtual void PlayerTick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	void Move(const struct FInputActionValue& InputActionValue);
	void CursorTrace();

private:
	UPROPERTY(EditAnywhere, Category  = "Input")
	TObjectPtr<class UInputMappingContext> AuraInputMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> AuraMoveInputAction;

	UPROPERTY()
	TScriptInterface<class IEnemyInterface> LastActor; // The previous actor under the mouse cursor (from the previous frame)

	UPROPERTY()
	TScriptInterface<class IEnemyInterface> ThisActor; // The current actor under the mouse cursor (from the current frame)
};
