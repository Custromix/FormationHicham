// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FormationHicham/FirstPersonShooterTemplate/FormationHichamCharacter.h"
#include "GameFramework/PlayerController.h"
#include "HichamPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FORMATIONHICHAM_API AHichamPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Blueprintable, Category = Input)
	UInputMappingContext* InputMappingContext;

protected:
	virtual void BeginPlay() override;
};
