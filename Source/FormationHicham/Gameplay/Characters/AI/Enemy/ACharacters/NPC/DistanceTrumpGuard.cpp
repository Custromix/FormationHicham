// Fill out your copyright notice in the Description page of Project Settings.


#include "DistanceTrumpGuard.h"

#include "FormationHicham/Gameplay/Items/Interfaces/FireInterface.h"
#include "FormationHicham/Gameplay/Items/Weapons/WeaponBase.h"


// Sets default values
ADistanceTrumpGuard::ADistanceTrumpGuard()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ADistanceTrumpGuard::BeginPlay()
{
	Super::BeginPlay();

	if (!ItemData) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "ItemData Non Set"); return; }
	if (!ItemClass) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "ItemClass Non Set"); return; }
	
	WeaponComponent->SetChildActorClass(ItemClass);

	FActorSpawnParameters Params;
	Params.Owner = this;
	EquippedItemActor = GetWorld()->SpawnActor<AItem>(ItemData->ItemClass, Params);
	EquippedItemActor->Initialize(ItemData);
	EquippedItemActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "S_Weapon");
	//FTransform LHIKTransform = GetItemSocketTransformInMeshSpace("LHIK");
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
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "EquippedItemActor Non Set");
		StopAttack();
		return;
	}
	//EquippedItemActor->GetSkeletalMesh()->GetSocketLocation("MuzzleFlash")
	FVector EyeLocation;
	FRotator EyeRotation;
	GetActorEyesViewPoint(EyeLocation, EyeRotation);
	
	if (IFireInterface::Execute_TryFire(EquippedItemActor, EyeLocation, EyeRotation.Vector(), this))
	{
		StartMontage();
		return;
	}else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Execute_TryFire Failed");
	}
		return; //Play Empty magazine sound
}

void ADistanceTrumpGuard::StopAttack()
{
	Super::StopAttack();
	
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Fire);
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_StopTimer);
	
	OnAttackFinished.Broadcast(this);
}

