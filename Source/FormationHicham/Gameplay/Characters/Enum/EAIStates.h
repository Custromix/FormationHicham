// TeamTypes.h
#pragma once
#include "UObject/ObjectMacros.h"

UENUM(BlueprintType)
enum class EAIState : uint8
{
    Idle,
    Hiding,
    Chasing
};