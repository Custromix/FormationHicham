// Fill out your copyright notice in the Description page of Project Settings.


#include "FormationTestGameMode.h"

#include "FormationHicham/Core/HUD/FormationTestHud.h"
#include "GameFramework/GameStateBase.h"
#include "Kismet/GameplayStatics.h"


void AFormationTestGameMode::BeginPlay()
{
	Super::BeginPlay();
}

bool AFormationTestGameMode::RequestRestartGame()
{
	if (MatchState == MatchState::LeavingMap){
		RestartGame();
		return true;
	}
	return false;
}

bool AFormationTestGameMode::RequestFinishGame()
{
	if (MatchState == MatchState::InProgress)
	{
		FinishGame();
		return true;
	}
	return false;
}

bool AFormationTestGameMode::RequestFinalBossStart()
{
	FinalBossStart();
	return true;
}

void AFormationTestGameMode::RestartGame()
{
	const FName CurrentLevelName = *GetWorld()->GetName();

	UGameplayStatics::OpenLevel(GetWorld(), CurrentLevelName);
}

void AFormationTestGameMode::FinishGame()
{
	GameState->Reset();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->SetPause(true);
	
	OnFinishGame.Broadcast();
	SetMatchState(MatchState::LeavingMap);
	
}

void AFormationTestGameMode::FinalBossStart()
{
	OnFinalBoss.Broadcast();
}
