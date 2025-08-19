// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FormationHicham/Gameplay/Items/Item.h"
#include "Ammo.generated.h"

UENUM(BlueprintType, Blueprintable)
enum class EAmmoType : uint8
{
	C9MM      UMETA(DisplayName = "Calibre 9mm"),
	C545X39   UMETA(DisplayName = "Calibre 5.45x39"),
	C12		  UMETA(DisplayName = "Calibre 12"),
};

UCLASS()
class FORMATIONHICHAM_API AAmmo : public AItem
{
	GENERATED_BODY()

public:
	
	AAmmo();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
	EAmmoType AmmoType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
	int32 AmmoAmount;

public:
	UFUNCTION(BlueprintCallable, Category = Ammo)
	EAmmoType GetAmmoType() const { return AmmoType; };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
	int32 GetAmmoAmount() const { return AmmoAmount; };
};
