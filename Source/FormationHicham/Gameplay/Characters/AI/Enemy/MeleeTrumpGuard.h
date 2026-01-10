// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TrumpGuardBase.h"
#include "MeleeTrumpGuard.generated.h"

UCLASS()
class FORMATIONHICHAM_API AMeleeTrumpGuard : public ATrumpGuardBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMeleeTrumpGuard();

protected:
	virtual void BeginPlay() override;
	
public:
	virtual void StartAttack() override;
	virtual void StopAttack() override;

	void BatonTrace();

protected:
	UPROPERTY(EditAnywhere, Category = "Attack AI")
	float CapsuleRadius = 12.f;

	UPROPERTY(EditAnywhere, Category = "Attack AI")
	float LoopTime = 0.034;

	UPROPERTY(EditAnywhere, Category = "Attack AI", meta=(DevelopmentOnly))
	float DrawTime = 0.5;

private:
	TArray<UArrowComponent*> ArrowsComponents;
	
	FTimerHandle TimerHandle_Attack;

	bool bCanAttack = true;
};