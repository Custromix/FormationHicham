// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"


// Sets default values
AWeaponBase::AWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponBase::Fire(FVector ViewportSize)
{
	ServerHandleFire(ViewportSize);
}

void AWeaponBase::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Collide");
}

void AWeaponBase::ServerHandleFire_Implementation(FVector ViewportSize)
{
	FHitResult HitResult;
	FVector Start = ViewportSize;   // Position de départ (souvent la caméra)
	FVector End = ViewportSize;     // Position d’arrivée (Start + direction * distance)

	

	// Et ensuite :

	bool bHit = GetWorld()->LineTraceSingleByChannel(
	HitResult,
	Start,
	End,
	ECC_Visibility
	);
}