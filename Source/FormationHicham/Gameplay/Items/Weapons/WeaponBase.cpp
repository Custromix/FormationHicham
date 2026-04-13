// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"

#include "Engine/DamageEvents.h"
#include "FormationHicham/Gameplay/Items/EItemType.h"

AWeaponBase::AWeaponBase()
{
	ItemType = EItemType::WEAPON;

	PrimaryActorTick.bCanEverTick = true;
}

void AWeaponBase::Initialize(UItemData* AItemData)
{
	Super::Initialize(AItemData);

	if (!AItemData)
		return;
	
	WeaponInfoDataAsset = Cast<UWeaponDataAsset>(AItemData);
	if (!WeaponInfoDataAsset)
		return;

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Purple, WeaponInfoDataAsset->GetName());
	
	/* Set 1 magazine to the weapon */
	WeaponInfoDataAsset->CurrentAmmo = WeaponInfoDataAsset->MagazineCapacity;
	WeaponInfoDataAsset->RemainingAmmo = 50;
	FireRateSeconds = 1/WeaponInfoDataAsset->FireRate;
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
	GEngine->AddOnScreenDebugMessage(3, 2.f, FColor::Green, FString::Printf(TEXT("Current Bullet : %d/%d"), WeaponInfoDataAsset->CurrentAmmo, WeaponInfoDataAsset->RemainingAmmo));
}

bool AWeaponBase::TryFire_Implementation(const FVector Location, const FVector ForwardVector)
{
	if (!WeaponInfoDataAsset) return false;
	if (!bCanFire) return false;
	if (WeaponInfoDataAsset->CurrentAmmo <= 0) return false;
	
	float DeltaFireTime = GetWorld()->GetTime().GetWorldTimeSeconds() - LastTimeAfterFire;

	if (DeltaFireTime >= FireRateSeconds)
	{
		GetSkeletalMesh()->PlayAnimation(WeaponInfoDataAsset->AnimationData->WeaponFire, false);
		Fire(Location, ForwardVector);
		LastTimeAfterFire = GetWorld()->GetTime().GetWorldTimeSeconds();
		return true;
	}else
	{
		return false;
	}
}

void AWeaponBase::Fire(FVector Start, FVector End)
{
	FHitResult HitResult;
	TArray<AActor*> IgnoredActors = { this, GetOwner() };
	FCollisionQueryParams Params;
	Params.AddIgnoredActors(IgnoredActors);
	Params.AddIgnoredActor(GetOwner());
	
	bool bHit = GetWorld()->LineTraceSingleByChannel(
	HitResult,
	Start,
	Start + End * WeaponInfoDataAsset->MaxRange,
	ECC_Visibility
	);
	
	if (bHit)
	{
		DrawDebugLine(GetWorld(), Start, HitResult.Location, FColor::Red, false, 2.0f);

		FDamageEvent DamageEvent;
		if (WeaponInfoDataAsset->DamageType == EDamageType::POINT)
		{
			FPointDamageEvent DamageType;
			HitResult.GetActor()->TakeDamage(WeaponInfoDataAsset->Damage, DamageType, GetInstigatorController(), GetOwner());
		}else
		{
			FRadialDamageEvent DamageType;
			HitResult.GetActor()->TakeDamage(WeaponInfoDataAsset->Damage, DamageType, GetInstigatorController(), GetOwner());
		}
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, "FIRE");

		WeaponInfoDataAsset->CurrentAmmo--;
		if (WeaponInfoDataAsset->CurrentAmmo <= 0)
			bCanFire = false;
			
	}
	else DrawDebugLine(GetWorld(), Start, End * WeaponInfoDataAsset->MaxRange, FColor::Green, false, 2.0f);
	
}

bool AWeaponBase::TrySecondaryFire_Implementation()
{
	return ISecondaryFireInterface::TrySecondaryFire_Implementation();
}

bool AWeaponBase::CanReload()
{
	return WeaponInfoDataAsset->CurrentAmmo < WeaponInfoDataAsset->MagazineCapacity && WeaponInfoDataAsset->RemainingAmmo > 0; 
}

bool AWeaponBase::TryReload_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "Jee appuie");
	
	if (!CanReload())
		return false;
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, "RELOAD OUIIII");
	bCanFire = false;
	GetSkeletalMesh()->PlayAnimation(WeaponInfoDataAsset->AnimationData->WeaponReload, false);
	
	return true;
}

void AWeaponBase::Reload()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "RELOAD");
	
	const int32 NeededAmmo = WeaponInfoDataAsset->MagazineCapacity - WeaponInfoDataAsset->CurrentAmmo;
	const int32 AmmoToReload = FMath::Min(NeededAmmo, WeaponInfoDataAsset->RemainingAmmo);

	WeaponInfoDataAsset->CurrentAmmo += AmmoToReload;
	WeaponInfoDataAsset->RemainingAmmo -= AmmoToReload;
	 
	bCanFire = true;
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
