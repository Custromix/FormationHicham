// TrumpGuard.cpp
#include "TrumpGuardBase.h"

ATrumpGuardBase::ATrumpGuardBase()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	HealthComponent->OnDeath.AddDynamic(this, &ATrumpGuardBase::OnDeath);
}

void ATrumpGuardBase::BeginPlay()
{
	Super::BeginPlay();
}

void ATrumpGuardBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


