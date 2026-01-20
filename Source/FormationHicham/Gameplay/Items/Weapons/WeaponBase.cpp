// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"

#include "Engine/DamageEvents.h"
#include "FormationHicham/Gameplay/Items/EItemType.h"

AWeaponBase::AWeaponBase()
{
	ItemType = EItemType::WEAPON;
	
}

void AWeaponBase::Initialize(UItemData* AItemData)
{
	Super::Initialize(AItemData);

	if (AItemData)
		WeaponInfoDataAsset = Cast<UWeaponDataAsset>(AItemData);
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWeaponBase::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponBase::Fire(FVector Start, FVector End)
{
	
}

void AWeaponBase::Use_Implementation(UCameraComponent* PlayerCamera)
{
	if (!WeaponInfoDataAsset)
		return;
	
	FVector Start = PlayerCamera->GetComponentLocation();
	FVector End = PlayerCamera->GetForwardVector();
	
	FHitResult HitResult;
	
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	
	bool bHit = GetWorld()->LineTraceSingleByChannel(
	HitResult,
	Start,
	Start + End * 5000.0f,
	ECC_Visibility
	);
	
	if (bHit)
	{
		DrawDebugLine(GetWorld(), Start, HitResult.Location, FColor::Red, false, 2.0f);
		
		if (WeaponInfoDataAsset->DamageType == EDamageType::POINT)
		{
			FPointDamageEvent DamageType;
			HitResult.GetActor()->TakeDamage(WeaponInfoDataAsset->Damage, DamageType, GetInstigatorController(), GetOwner());
		}else
		{
			FRadialDamageEvent DamageType;
			HitResult.GetActor()->TakeDamage(WeaponInfoDataAsset->Damage, DamageType, GetInstigatorController(), GetOwner());
		}
	}
	else DrawDebugLine(GetWorld(), Start, End, FColor::Blue, false, 2.0f);
}

void AWeaponBase::Aim_Implementation()
{
	IAimableInterface::Aim_Implementation();
}

void AWeaponBase::Reload_Implementation()
{
	IReloadableInterface::Reload_Implementation();
}

void AWeaponBase::ServerHandleFire_Implementation(const FVector3d ViewportSize)
{
	FHitResult HitResult;
	const FVector Start = ViewportSize;
	const FVector End = ViewportSize;
	
	bool bHit = GetWorld()->LineTraceSingleByChannel(
	HitResult,
	Start,
	End,
	ECC_Visibility
	);
}

void AWeaponBase::ServerHandleAim_Implementation()
{
}

void AWeaponBase::ServerHandleReload_Implementation()
{
}

void AWeaponBase::ServerHandleDrop_Implementation()
{
}




