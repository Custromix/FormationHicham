// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FormationHicham/Gameplay/Items/Ammo/Ammo.h"
#include "GeometryCollection/GeometryCollectionSimulationTypes.h"
#include "WeaponDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class FORMATIONHICHAM_API UWeaponDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	FName Name;

	UPROPERTY(EditAnywhere)
	EAmmoType AmmoType;

	UPROPERTY(EditAnywhere)
	int32 AmmoMax;

	UPROPERTY(EditAnywhere)
	int32 CurrentAmmo;

	UPROPERTY(EditAnywhere)
	float Damage;

	EDamageType DamageType;
};

UENUM(BlueprintType)
enum class EDamageType : uint8
{
	POINT  UMETA(DisplayName="Point"),
	RADIAL UMETA(DisplayName="Radial"),
};

