// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TrumpGuardAIControllerBase.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "DistanceTrumpGuardAIController.generated.h"

UCLASS()
class FORMATIONHICHAM_API ADistanceTrumpGuardAIController : public ATrumpGuardAIControllerBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADistanceTrumpGuardAIController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus) override;

	UFUNCTION()
	void OnForgetTarget(AActor* Player);

public:
	virtual void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere)
	AActor* Target;
};


