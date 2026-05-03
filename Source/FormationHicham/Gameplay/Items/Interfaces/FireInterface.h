// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "UObject/Interface.h"
#include "FireInterface.generated.h"

UINTERFACE(Blueprintable)
class UFireInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface pour objets utilisables
 */
class FORMATIONHICHAM_API IFireInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Item Use")
	bool TryFire(const FVector Location, const FVector ForwardVector, AActor* IgnoredActor = nullptr);

};
