// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MeleeAttackInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UMeleeAttackInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FORMATIONHICHAM_API IMeleeAttackInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Attack AI")
	void StartMeleeAttack();
};
