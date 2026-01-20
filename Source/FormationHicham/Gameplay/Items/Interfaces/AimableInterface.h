// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AimableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UAimableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FORMATIONHICHAM_API IAimableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Item Use")
	void Aim();
};
