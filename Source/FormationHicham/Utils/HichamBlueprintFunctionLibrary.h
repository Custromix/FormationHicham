// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HichamBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class FORMATIONHICHAM_API UHichamBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Rendering|Material")
	static bool SetStaticSwitchParameterValue(UMaterialInstance* Instance, FName ParameterName, bool Value);
};
