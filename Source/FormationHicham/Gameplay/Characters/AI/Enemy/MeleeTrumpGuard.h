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

	virtual void Attack() override;

protected:
	
	UPROPERTY(EditAnywhere)
	float Radius;

	UPROPERTY(EditAnywhere)
	UArrowComponent* ArrowStart;
	
	UPROPERTY(EditAnywhere)
	UArrowComponent* ArrowEnd;
	
};