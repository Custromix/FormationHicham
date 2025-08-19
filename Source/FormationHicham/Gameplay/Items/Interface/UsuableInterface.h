// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UsuableInterface.generated.h"

UINTERFACE(Blueprintable)
class UUsuableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface pour objets utilisables
 */
class FORMATIONHICHAM_API IUsuableInterface
{
	GENERATED_BODY()

public:

	// Ces fonctions doivent être implémentées dans les classes qui héritent
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Usable")
	void FirstUse(class AHichamCharacter* HichamCharacter);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Usable")
	void SecondUse(class AHichamCharacter* HichamCharacter);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Usable")
	void ThirdUse(class AHichamCharacter* HichamCharacter);
};
