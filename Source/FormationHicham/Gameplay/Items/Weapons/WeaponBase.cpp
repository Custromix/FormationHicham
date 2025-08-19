// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"

AWeaponBase::AWeaponBase()
{
	ItemType = EItemType::WEAPON;
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

void AWeaponBase::Reload()
{
}

void AWeaponBase::FirstUse_Implementation(AHichamCharacter* HichamCharacter)
{
}

void AWeaponBase::SecondUse_Implementation(AHichamCharacter* HichamCharacter)
{
}

void AWeaponBase::ThirdUse_Implementation(AHichamCharacter* HichamCharacter)
{
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
