// Copyright Richard Skala


#include "Character/AuraCharacterBase.h"

//DECLARE_LOG_CATEGORY_EXTERN(LogAuraCharacterBase, Log, Log)
DEFINE_LOG_CATEGORY(LogAuraCharacterBase)

// Sets default values
AAuraCharacterBase::AAuraCharacterBase()
{
	UE_LOG(LogAuraCharacterBase, Warning, TEXT("AAuraCharacterBase::AAuraCharacterBase"));

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bCanEverTick = false;

	// Create the Weapon SkeletalMesh default subobject
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");

	// Attach the weapon to a socket on the mesh -- This sets the Weapon as a child of the Mesh (which is inherited from ACharacter class)
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket")); // This creates a socket on one of the hands and the weapon will be attached to that
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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
	//UE_LOG(LogAuraCharacterBase, Log, TEXT("AAuraCharacterBase::Tick"));
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
	Super::PreInitializeComponents();
}

void AAuraCharacterBase::PostInitializeComponents()
{
	UE_LOG(LogAuraCharacterBase, Log, TEXT("AAuraCharacterBase::PostInitializeComponents"));
	Super::PostInitializeComponents();
}


