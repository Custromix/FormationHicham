// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CheckDistance.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_CheckDistance::UBTDecorator_CheckDistance()
{
	NodeName = TEXT("IsTargetAway");
}

bool UBTDecorator_CheckDistance::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	if (!BB)
		return false;

	const float Distance = BB->GetValueAsFloat(BlackboardKey.SelectedKeyName);
	
	return Distance <= MaxDistance && Distance != 0;
}

