// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeTrumpGuard.h"

#include "KismetTraceUtils.h"
#include "Components/ArrowComponent.h"
#include "Engine/DamageEvents.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
AMeleeTrumpGuard::AMeleeTrumpGuard()
{
}

void AMeleeTrumpGuard::BeginPlay()
{
	Super::BeginPlay();
	GetComponents<UArrowComponent>(ArrowsComponents);
	ArrowsComponents.RemoveAll(
		[](UArrowComponent* Arrow)
		{
			return !Arrow || !Arrow->ComponentHasTag("ArrowInitializer");
		}
	);
	
}

void AMeleeTrumpGuard::StartAttack()
{
	Super::StartAttack();

	if (ArrowsComponents.IsEmpty())
		return;

	bCanAttack = true;
	
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle_Attack,
		this,
		&AMeleeTrumpGuard::BatonTrace,
		LoopTime,   
		true
	);
	
}

void AMeleeTrumpGuard::StopAttack()
{
	Super::StopAttack();
	
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Attack);
	
	OnAttackFinished.Broadcast();
}

void AMeleeTrumpGuard::BatonTrace()
{
	const FVector Start = ArrowsComponents[0]->GetComponentLocation();
	const FVector End = ArrowsComponents[1]->GetComponentLocation();
	
	FHitResult SphereTraceResult;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	
	bool bHit = UKismetSystemLibrary::SphereTraceSingle(
	this,
	Start,
	End,
	CapsuleRadius,
	UEngineTypes::ConvertToTraceType(ECC_Pawn),
	false,
	ActorsToIgnore,
	EDrawDebugTrace::ForDuration,
	SphereTraceResult,
	true,
	FColor::Red,
	FColor::Green,
	DrawTime
	);

	/*bool bHit2 = GetWorld()->SweepSingleByChannel(
	SphereTraceResult,
	Start,
	End,
	FQuat::Identity,
	ECC_Visibility,
	FCollisionShape::MakeSphere(CapsuleRadius),
	QueryParams);*/
	
	//*DrawDebugSphereTraceSingle(GetWorld(),Start, End, 12.f, EDrawDebugTrace::ForDuration, bHit2, SphereTraceResult, FColor::Red, FColor::Green, DrawTime);
	
	if (bHit)
	{
		if (!SphereTraceResult.GetActor())
			return;

		if (bCanAttack)
		{
			FDamageEvent DamageEvent;
			SphereTraceResult.GetActor()->TakeDamage(10.f, DamageEvent, GetController(), this);
			bCanAttack = false;
		}
	}
}



