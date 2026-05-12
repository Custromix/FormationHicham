// Fill out your copyright notice in the Description page of Project Settings.


#include "TrumpAIController.h"


// Sets default values
ATrumpAIController::ATrumpAIController()
{
	
}

// Called when the game starts or when spawned
void ATrumpAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATrumpAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	Super::OnTargetPerceptionUpdated(Actor, Stimulus);
}

