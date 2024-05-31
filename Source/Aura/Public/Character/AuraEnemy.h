// Copyright Richard Skala

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"

#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
	
public:
	// Inherited via IEnemyInterface
	void HighlightActor() override;
	void UnhighlightActor() override;

private:
	UPROPERTY(BlueprintReadOnly , meta = (AllowPrivateAccess = true))
	bool bHighlighted = false;
};
