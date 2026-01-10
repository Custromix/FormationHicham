// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "FormationTestGameState.generated.h"

/**
 * 
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
	int32 GetGlobalScore () const { return GlobalScore; }
	void SetGlobalScore(const int32 GlobalScore) { this->GlobalScore = GlobalScore; }

private:
	int32 GlobalScore = 0;
	
};
