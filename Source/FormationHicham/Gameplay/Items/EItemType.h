// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EItemType.generated.h"

/**
 * 
 */
UENUM(BlueprintType, Blueprintable)
enum class EItemType : uint8
{
	AMMO        UMETA(DisplayName = "Ammo"),
	WEAPON      UMETA(DisplayName = "Weapon"),
	CONSUMABLE  UMETA(DisplayName = "Consumable"),
	OTHER  UMETA(DisplayName = "Other"),
};
