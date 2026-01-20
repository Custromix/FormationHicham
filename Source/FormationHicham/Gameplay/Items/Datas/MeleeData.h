// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"
#include "MeleeData.generated.h"

/**
 * 
 */
UCLASS()
class FORMATIONHICHAM_API UMeleeData : public UItemData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float QuickMeleeDamage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SlowMeleeDamage;
};
