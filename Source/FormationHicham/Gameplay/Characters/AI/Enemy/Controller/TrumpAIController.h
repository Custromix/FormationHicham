// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TrumpGuardAIControllerBase.h"
#include "TrumpAIController.generated.h"

UCLASS()
class FORMATIONHICHAM_API ATrumpAIController : public ATrumpGuardAIControllerBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATrumpAIController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus) override;
	
};
