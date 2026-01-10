// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_Blackboard.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTDecorator_CheckDistance.generated.h"

/**
 * 
 */
UCLASS()
class FORMATIONHICHAM_API UBTDecorator_CheckDistance : public UBTDecorator_Blackboard
{
	GENERATED_BODY()

public:
	UBTDecorator_CheckDistance();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

protected:
	UPROPERTY(EditAnywhere)
	float MaxDistance = 125.f;

};
