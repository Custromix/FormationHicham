// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "FormationTestGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChanged, int, Score);

/**
 * GameState of game
 */
UCLASS()
class FORMATIONHICHAM_API AFormationTestGameState : public AGameState
{
	GENERATED_BODY()

public:
		AFormationTestGameState();
	
protected:
	virtual void BeginPlay() override;

	virtual void Reset() override;

public:
	UFUNCTION(BlueprintCallable, Category = "Score")
	int32 GetGlobalScore () const { return GlobalScore; }

	UPROPERTY(BlueprintAssignable, Category = "Delegates")
	FOnScoreChanged OnScoreChanged;
	
	void IncrementScore(const int32 AddedScore);

private:
	int32 GlobalScore = 0;
	
};
