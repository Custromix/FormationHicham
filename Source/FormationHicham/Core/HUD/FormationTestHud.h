// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "GameFramework/HUD.h"
#include "FormationTestHud.generated.h"

/**
 * 
 */
UCLASS()
class FORMATIONHICHAM_API AFormationTestHud : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TSubclassOf<UUserWidget> EndgameWidgetClass;
};
