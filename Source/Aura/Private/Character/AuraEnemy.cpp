// Copyright Richard Skala


#include "Aura/Aura.h"
#include "Character/AuraEnemy.h"

DEFINE_LOG_CATEGORY_STATIC(LogAuraEnemy, Log, All)

AAuraEnemy::AAuraEnemy()
{
	// Set correct collision response
	if (USkeletalMeshComponent* EnemySkeletalMesh = GetMesh())
	{
		EnemySkeletalMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	}
}

void AAuraEnemy::HighlightActor()
{
	UE_LOG(LogAuraEnemy, Log, TEXT("AAuraEnemy::HighlightActor - %s"), *GetName());
	bHighlighted = true;

	// Highlight the enemy
	if (USkeletalMeshComponent* EnemySkeletalMesh = GetMesh())
	{
		EnemySkeletalMesh->SetRenderCustomDepth(true);
		EnemySkeletalMesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	}

	// Highlight the enemy weapon
	if (Weapon != nullptr)
	{
		Weapon->SetRenderCustomDepth(true);
		Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	}
}

void AAuraEnemy::UnhighlightActor()
{
	UE_LOG(LogAuraEnemy, Log, TEXT("AAuraEnemy::UnhighlightActor - %s"), *GetName());
	bHighlighted = false;

	// Unhighlight the enemy
	if (USkeletalMeshComponent* EnemySkeletalMesh = GetMesh())
	{
		EnemySkeletalMesh->SetRenderCustomDepth(false);
	}

	// Unhighlight the enemy weapon
	if (Weapon != nullptr)
	{
		Weapon->SetRenderCustomDepth(false);
	}
}
