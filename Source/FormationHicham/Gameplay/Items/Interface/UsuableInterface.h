// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UsuableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UUsuableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FORMATIONHICHAM_API IUsuableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void FirstUse(AHichamCharacter* HichamCharacter);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SecondUse(AHichamCharacter* HichamCharacter);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ThirdUse(AHichamCharacter* HichamCharacter);
};
