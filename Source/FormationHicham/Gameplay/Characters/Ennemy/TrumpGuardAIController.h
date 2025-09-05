// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "TrumpGuardAIController.generated.h"

UCLASS()
class FORMATIONHICHAM_API ATrumpGuardAIController : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATrumpGuardAIController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(VisibleAnywhere, Category="AI")
	UAIPerceptionComponent* Perception = nullptr;

	UPROPERTY()
	UAISenseConfig_Sight* SightConfig = nullptr;

	// Option 2 : assigner le BT ici si tu préfères (sinon via le Pawn)
	UPROPERTY(EditDefaultsOnly, Category="AI")
	UBehaviorTree* DefaultBehaviorTree = nullptr;

	UFUNCTION()
	void HandleTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};
