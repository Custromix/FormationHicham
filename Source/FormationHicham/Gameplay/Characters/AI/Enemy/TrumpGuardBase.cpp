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

void ATrumpGuardBase::OnDeath()
{
	Destroy();
}

void ATrumpGuardBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATrumpGuardBase::StartAttackAnim() const
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, "Attaque");
	GetMesh()->PlayAnimation(AttackAnimMontage, false);
}


