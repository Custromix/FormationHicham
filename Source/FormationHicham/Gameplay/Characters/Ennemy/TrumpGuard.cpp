// TrumpGuard.cpp
#include "TrumpGuard.h"

ATrumpGuard::ATrumpGuard()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	HealthComponent->OnDeath.AddDynamic(this, &ATrumpGuard::OnDeath);
}

void ATrumpGuard::BeginPlay()
{
	Super::BeginPlay();

}

void ATrumpGuard::OnDeath()
{
	Destroy();
}

void ATrumpGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
