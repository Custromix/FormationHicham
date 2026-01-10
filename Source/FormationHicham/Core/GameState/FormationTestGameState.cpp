// Fill out your copyright notice in the Description page of Project Settings.


#include "FormationTestGameState.h"

#include "GameFramework/GameMode.h"

AFormationTestGameState::AFormationTestGameState()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AFormationTestGameState::BeginPlay()
{
	Super::BeginPlay();
}

void AFormationTestGameState::Reset()
{
	Super::Reset();
}

void AFormationTestGameState::IncrementScore(const int32 AddedScore)
{
	this->GlobalScore += AddedScore;
	GEngine->AddOnScreenDebugMessage(3, 5, FColor::Purple, FString::Printf(TEXT("Score Incremented : %i" ), GlobalScore));
}

