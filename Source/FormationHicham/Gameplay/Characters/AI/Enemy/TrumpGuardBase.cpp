// TrumpGuard.cpp
#include "TrumpGuardBase.h"

#include "GameFramework/CharacterMovementComponent.h"

ATrumpGuardBase::ATrumpGuardBase()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	HealthComponent->OnDeath.AddDynamic(this, &ATrumpGuardBase::OnDeath);

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ATrumpGuardBase::BeginPlay()
{
	Super::BeginPlay();
}

void ATrumpGuardBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATrumpGuardBase::WhenPlayerSeen()
{
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void ATrumpGuardBase::WhenPlayerUnseen()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}


