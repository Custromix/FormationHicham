// Fill out your copyright notice in the Description page of Project Settings.


#include "HichamPlayerController.h"

#include "EnhancedInputSubsystems.h"

void AHichamPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}
