// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MeleeTrumpGuard.h"
#include "FormationHicham/Gameplay/Items/Item.h"
#include "DistanceTrumpGuard.generated.h"

UCLASS()
class FORMATIONHICHAM_API ADistanceTrumpGuard : public ATrumpGuardBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADistanceTrumpGuard();

protected:
	virtual void BeginPlay() override;

	void TryFire();
	
public:
	virtual void StartAttack() override;
	virtual void StopAttack() override;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Attack AI/Inventory")
	AItem* EquippedItemActor;
	
	UPROPERTY(EditAnywhere, Category = "Attack AI/Param")
	float FireInterval_S = 0.1;
	
	UPROPERTY(EditAnywhere, Category = "Attack AI/Param")
	float AttackDuration_S = 2.f;
	
private:

	FTimerHandle TimerHandle_Fire;
	
	FTimerHandle TimerHandle_StopTimer;
};
