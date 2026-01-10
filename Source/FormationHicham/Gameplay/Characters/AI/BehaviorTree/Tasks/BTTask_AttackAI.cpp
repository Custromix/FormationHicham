// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_AttackAI.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTask_AttackAI::UBTTask_AttackAI()
{
	
}

EBTNodeResult::Type UBTTask_AttackAI::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	CachedOwnerComponent = &OwnerComp;
	TrumpGuard = Cast<ATrumpGuardBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("SelfActor"));
	
	if (TrumpGuard)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, "Attaque");
		TrumpGuard->StartMontage();
		TrumpGuard->OnAttackFinished.AddDynamic(this, &UBTTask_AttackAI::OnAttackFinished);
		return EBTNodeResult::InProgress;
	}else
		return EBTNodeResult::Failed;
}

EBTNodeResult::Type UBTTask_AttackAI::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (TrumpGuard)
	{
		//TrumpGuard->StopMontage();
		TrumpGuard->OnAttackFinished.RemoveDynamic(this,&UBTTask_AttackAI::OnAttackFinished);
	}
	
	return Super::AbortTask(OwnerComp, NodeMemory);
}

void UBTTask_AttackAI::OnAttackFinished()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, "Attaque FINI");

	if (!CachedOwnerComponent)
		return;
	
	if (!TrumpGuard)
		return;

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, "Attaque FINI");

	//TrumpGuard->StopMontage();
	TrumpGuard->OnAttackFinished.RemoveDynamic(this,&UBTTask_AttackAI::OnAttackFinished);
	FinishLatentTask(*CachedOwnerComponent, EBTNodeResult::Succeeded);
}
