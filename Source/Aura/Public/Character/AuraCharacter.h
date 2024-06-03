// Copyright Richard Skala

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:
	AAuraCharacter();

	// Inherited from APawn
	virtual void OnRep_PlayerState() override;

	// Inherited from ACharacter
	virtual void PossessedBy(AController* NewController) override;

private:
	void InitAbilityActorInfo();
};
