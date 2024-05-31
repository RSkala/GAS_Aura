// Copyright Richard Skala


#include "Character/AuraEnemy.h"

DEFINE_LOG_CATEGORY_STATIC(LogAuraEnemy, Log, All)

void AAuraEnemy::HighlightActor()
{
	UE_LOG(LogAuraEnemy, Log, TEXT("AAuraEnemy::HighlightActor - %s"), *GetName());
	bHighlighted = true;
}

void AAuraEnemy::UnhighlightActor()
{
	UE_LOG(LogAuraEnemy, Log, TEXT("AAuraEnemy::UnhighlightActor - %s"), *GetName());
	bHighlighted = false;
}
