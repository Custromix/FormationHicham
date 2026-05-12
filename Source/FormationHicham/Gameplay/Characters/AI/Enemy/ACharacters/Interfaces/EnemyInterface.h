// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "UObject/Interface.h"
#include "EnemyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface pour les ennemis (IA)
 */
class FORMATIONHICHAM_API IEnemyInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual UBehaviorTree* GetBehaviorTree() = 0;

	virtual void WhenPlayerSeen() = 0;

	virtual void WhenPlayerUnseen() = 0;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Attack")
	void Attack();
	
protected:
	UBehaviorTree* BehaviorTree;
};
