// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
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
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Item Use")
	void Use(UCameraComponent* PlayerCamera);

};
