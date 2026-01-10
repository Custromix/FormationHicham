// Fill out your copyright notice in the Description page of Project Settings.


#include "FormationTestGameMode.h"

#include "FormationHicham/Core/HUD/FormationTestHud.h"
#include "GameFramework/GameStateBase.h"
#include "Kismet/GameplayStatics.h"


void AFormationTestGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AFormationTestGameMode::RequestRestartGame()
{
	if (MatchState == MatchState::LeavingMap)
		RestartGame();
}

void AFormationTestGameMode::RequestFinishGame()
{
	if (MatchState == MatchState::InProgress)
		FinishGame();
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

	AFormationTestHud* HUD = Cast<AFormationTestHud>(PlayerController->GetHUD());
	if (HUD)
	{
		HUD->DisplayEndGameUI();
		SetMatchState(MatchState::LeavingMap);
	}
}
