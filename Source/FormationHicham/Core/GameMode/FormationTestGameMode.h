// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "FormationTestGameMode.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFinishGame);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFinalBoss);
UCLASS()
class FORMATIONHICHAM_API AFormationTestGameMode : public AGameMode
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:
	UFUNCTION(BlueprintCallable, Category = "Game Settings")
	bool RequestRestartGame();
	
	UFUNCTION(BlueprintCallable, Category = "Game Settings")
	bool RequestFinishGame();
	
	UFUNCTION(BlueprintCallable, Category = "Game Settings")
	bool RequestFinalBossStart();
	
private:
	void RestartGame();
	void FinishGame();
	
	void FinalBossStart();

public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnFinishGame OnFinishGame;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnFinalBoss OnFinalBoss;
};
