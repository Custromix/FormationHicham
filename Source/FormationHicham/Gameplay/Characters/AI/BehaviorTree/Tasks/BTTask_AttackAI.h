// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "FormationHicham/Gameplay/Characters/AI/Enemy/TrumpGuardBase.h"
#include "BTTask_AttackAI.generated.h"

/**
 * 
 */

UCLASS()
class FORMATIONHICHAM_API UBTTask_AttackAI : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_AttackAI();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UFUNCTION()
	void OnAttackFinished();

private:
	UPROPERTY()
	UBehaviorTreeComponent* CachedOwnerComponent;

	ATrumpGuardBase* TrumpGuard;
};