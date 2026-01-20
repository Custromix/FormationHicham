// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"
#include "FormationHicham/Gameplay/Items/Ammos/Ammo.h"
#include "WeaponDataAsset.generated.h"

UENUM(BlueprintType)
enum class EDamageType : uint8
{
	POINT  UMETA(DisplayName="Point"),
	RADIAL UMETA(DisplayName="Radial"),
};

/**
 * 
 */
UCLASS()
class FORMATIONHICHAM_API UWeaponDataAsset : public UItemData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EAmmoType AmmoType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 AmmoMax;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 CurrentAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EDamageType DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAudioBus* FireSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAudioBus* AimSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAudioBus* ReloadSound;
};


