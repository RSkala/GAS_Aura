// Copyright Richard Skala


#include "AuraCharacterBase.h"

//DECLARE_LOG_CATEGORY_EXTERN(LogAuraCharacterBase, Log, Log)
DEFINE_LOG_CATEGORY(LogAuraCharacterBase)

// Sets default values
AAuraCharacterBase::AAuraCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAuraCharacterBase::BeginPlay()
{
	UE_LOG(LogAuraCharacterBase, Log, TEXT("AAuraCharacterBase::BeginPlay"));
	Super::BeginPlay();
}

// Called every frame
void AAuraCharacterBase::Tick(float DeltaTime)
{
	UE_LOG(LogAuraCharacterBase, Log, TEXT("AAuraCharacterBase::Tick"));
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AAuraCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UE_LOG(LogAuraCharacterBase, Log, TEXT("AAuraCharacterBase::SetupPlayerInputComponent"));
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAuraCharacterBase::PreInitializeComponents()
{
	UE_LOG(LogAuraCharacterBase, Log, TEXT("AAuraCharacterBase::PreInitializeComponents"));
}

void AAuraCharacterBase::PostInitializeComponents()
{
	UE_LOG(LogAuraCharacterBase, Log, TEXT("AAuraCharacterBase::PostInitializeComponents"));
}


