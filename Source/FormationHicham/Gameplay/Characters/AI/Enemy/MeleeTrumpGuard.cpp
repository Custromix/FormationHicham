// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeTrumpGuard.h"

#include "Components/ArrowComponent.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
AMeleeTrumpGuard::AMeleeTrumpGuard()
{
	ArrowStart = CreateDefaultSubobject<UArrowComponent>("ArrowStart");
	ArrowStart->SetupAttachment(RootComponent);
	ArrowEnd = CreateDefaultSubobject<UArrowComponent>("ArrowEnd");
	ArrowEnd->SetupAttachment(RootComponent);
}

void AMeleeTrumpGuard::Attack()
{
	Super::Attack();
	
	FHitResult SphereTraceResult;

	FVector Start = ArrowStart->GetComponentLocation();
	FVector End = ArrowEnd->GetComponentLocation();

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	
	bool bHit = GetWorld()->SweepSingleByChannel(
	SphereTraceResult,
	Start,
	End,
	FQuat::Identity,
	ECC_Visibility,
	FCollisionShape::MakeSphere(Radius),
	QueryParams
	);

	DrawDebugSphere(
		GetWorld(),
		bHit ? SphereTraceResult.ImpactPoint : End,
		Radius,
		16,
		bHit ? FColor::Red : FColor::Green,
		false,
		2.0f
	);
	
	if (bHit)
	{
		AActor* HitActor = SphereTraceResult.GetActor();
		UE_LOG(LogTemp, Warning, TEXT("Touché: %s"), *HitActor->GetName());
	}
}

