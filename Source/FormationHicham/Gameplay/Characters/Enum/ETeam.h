// TeamTypes.h
#pragma once
#include "UObject/ObjectMacros.h"

UENUM(BlueprintType)
enum class ETeamType : uint8
{
    Player   =  0     UMETA(DisplayName = "Player"),
    Ally     =  0     UMETA(DisplayName = "Ally"),
    Enemy    =  1  UMETA(DisplayName = "Enemy"),
    Neutral  =  255   UMETA(DisplayName = "Neutral"),
};
