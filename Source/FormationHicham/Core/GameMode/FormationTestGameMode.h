// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "FormationTestGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FORMATIONHICHAM_API AFormationTestGameMode : public AGameMode
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:
	UFUNCTION(BlueprintCallable, Category = "Game Settings")
	void RequestRestartGame();
	
	UFUNCTION(BlueprintCallable, Category = "Game Settings")
	void RequestFinishGame();
	
private:
	void RestartGame();
	void FinishGame();

};
