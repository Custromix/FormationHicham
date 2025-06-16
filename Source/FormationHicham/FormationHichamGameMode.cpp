// Copyright Epic Games, Inc. All Rights Reserved.

#include "FormationHichamGameMode.h"
#include "FormationHichamCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFormationHichamGameMode::AFormationHichamGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
