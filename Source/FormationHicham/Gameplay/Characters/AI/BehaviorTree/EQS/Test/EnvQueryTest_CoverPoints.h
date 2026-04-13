// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_CoverPoints.generated.h"

/**
 * 
 */
UCLASS()
class FORMATIONHICHAM_API UEnvQueryTest_CoverPoints : public UEnvQueryTest
{
	GENERATED_BODY()

public:
	UEnvQueryTest_CoverPoints();

protected:
	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;

	UPROPERTY(EditDefaultsOnly, Category="Trace")
	float SphereRadius = 50.f;

	UPROPERTY(EditDefaultsOnly, Category="Corner")
	float CornerTolerance = 30.f;
	
	UPROPERTY(EditDefaultsOnly, Category="Corner")
	float Offset = 10.f;
	
	UPROPERTY(EditDefaultsOnly, Category="Corner")
	float TimeSpanDebug = 2.f;

	UPROPERTY(EditAnywhere, Category = Filter, meta = (ClampMin = "0.0"))
	float CoverLength = 150.f;
};
