// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TrumpGuardAIControllerBase.h"
#include "Perception/AIPerceptionTypes.h"
#include "MeleeTrumpGuardAIController.generated.h"

UCLASS()
class FORMATIONHICHAM_API AMeleeTrumpGuardAIController : public ATrumpGuardAIControllerBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMeleeTrumpGuardAIController();

protected:
	virtual void BeginPlay() override;

	virtual void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus) override;
};
