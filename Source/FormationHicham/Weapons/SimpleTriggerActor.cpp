// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleTriggerActor.h"

#include "Components/CapsuleComponent.h"


ASimpleTriggerActor::ASimpleTriggerActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = Capsule;
	Capsule->InitCapsuleSize(55.f, 96.0f);
	Capsule->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	Capsule->OnComponentBeginOverlap.AddDynamic(this, &ASimpleTriggerActor::OnOverlapBegin);
}

void ASimpleTriggerActor::BeginPlay()
{
	Super::BeginPlay();
}

void ASimpleTriggerActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
										 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
										 bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Overlap detected!"));
	if (OtherActor && OtherActor != this)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Overlap detected!"));
	}
}

