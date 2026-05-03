// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_AttackAI.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_AttackAI::UBTTask_AttackAI()
{
	
}

EBTNodeResult::Type UBTTask_AttackAI::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	FBTAttackTaskMemory* Memory = reinterpret_cast<FBTAttackTaskMemory*>(NodeMemory);
	
	Memory->TrumpGuard = Cast<ATrumpGuardBase>(OwnerComponent.GetBlackboardComponent()->GetValueAsObject("SelfActor"));

	if (!Memory->TrumpGuard)
		return EBTNodeResult::Failed;
	
	Memory->TrumpGuard->StartAttack();
	Memory->TrumpGuard->OnAttackFinished.AddDynamic(this, &UBTTask_AttackAI::OnAttackFinished);
	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UBTTask_AttackAI::AbortTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	FBTAttackTaskMemory* Memory = reinterpret_cast<FBTAttackTaskMemory*>(NodeMemory);
	
	if (Memory->TrumpGuard)
	{
		Memory->TrumpGuard->OnAttackFinished.RemoveDynamic(this,&UBTTask_AttackAI::OnAttackFinished);
	}
	
	return Super::AbortTask(OwnerComponent, NodeMemory);
}

void UBTTask_AttackAI::OnAttackFinished(ATrumpGuardBase* Attacker)
{
	if (!Attacker)
		return;

	AAIController* AttackerController = Cast<AAIController>(Attacker->GetController());
	if (!AttackerController)
		return;

	UBehaviorTreeComponent* AttackerBehaviorTreeComponent = Cast<UBehaviorTreeComponent>(AttackerController->GetBrainComponent());
	if (!AttackerBehaviorTreeComponent)
		return;
	
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, "Attaque FINI");
	
	Attacker->OnAttackFinished.RemoveDynamic(this,&UBTTask_AttackAI::OnAttackFinished);
	FinishLatentTask(*AttackerBehaviorTreeComponent, EBTNodeResult::Succeeded);
}
