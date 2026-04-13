// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_CloserCorner.generated.h"

/**
 * 
 */
UCLASS()
class FORMATIONHICHAM_API UEnvQueryTest_CloserCorner : public UEnvQueryTest
{
	GENERATED_BODY()

public:
	UEnvQueryTest_CloserCorner();

protected:
	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
	
	UPROPERTY(EditDefaultsOnly, Category="Trace")
	float SphereRadius = 50.f;
	
	UPROPERTY(EditDefaultsOnly, Category="Trace")
	float CornerLength = 150.f;
};
