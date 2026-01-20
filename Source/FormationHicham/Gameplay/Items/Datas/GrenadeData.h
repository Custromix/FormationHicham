// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"
#include "GrenadeData.generated.h"

/**
 * 
 */
UCLASS()
class FORMATIONHICHAM_API UGrenadeData : public UItemData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grenade Data")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grenade Data")
	float Radius;
};
