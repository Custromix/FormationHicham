// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FormationTestHud.generated.h"

/**
 * 
 */
UCLASS()
class FORMATIONHICHAM_API AFormationTestHud : public AHUD
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DisplayEndGameUI();

	void DisplayEndGameUI_Implementation(){};

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TSubclassOf<UUserWidget> EndgameWidgetClass;
};
