// Fill out your copyright notice in the Description page of Project Settings.


#include "DistanceTrumpGuard.h"

#include "FormationHicham/Gameplay/Items/Interfaces/FireInterface.h"


// Sets default values
ADistanceTrumpGuard::ADistanceTrumpGuard()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ADistanceTrumpGuard::BeginPlay()
{
	Super::BeginPlay();
}

void ADistanceTrumpGuard::StartAttack()
{
	Super::StartAttack();

	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle_StopTimer,
		this,
		&ADistanceTrumpGuard::StopAttack,
		AttackDuration_S,
		false
	);

	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle_Fire,
		this,
		&ADistanceTrumpGuard::TryFire,
		FireInterval_S,
		true
	);
}

void ADistanceTrumpGuard::TryFire()
{
	if (!EquippedItemActor)
	{
		StopAttack();
		return;
	}
	
	if (IFireInterface::Execute_TryFire(EquippedItemActor,EquippedItemActor->GetSkeletalMesh()->GetSocketLocation("MuzzleFlash"), GetActorForwardVector()))
	{
		StartMontage();
		return;
	}else
		return; //Play Empty magazine sound
}

void ADistanceTrumpGuard::StopAttack()
{
	Super::StopAttack();
	
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Fire);
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_StopTimer);
	
	OnAttackFinished.Broadcast(this);
}

