// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandomLocation.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "FormationHicham/Gameplay/Characters/AI/Enemy/Controller/TrumpGuardAIControllerBase.h"

UBTTask_FindRandomLocation::UBTTask_FindRandomLocation()
{
	NodeName = "FindRandomLocation";
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	if (const ATrumpGuardAIControllerBase* OwnerAIController = Cast<ATrumpGuardAIControllerBase>(OwnerComp.GetAIOwner()))
	{
		if (const APawn* Npc = OwnerAIController->GetPawn())
		{
			const FVector NpcLocationOrigin =  Npc->GetActorLocation();

			if (const UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				FNavLocation NewNpcLocation;
				if (NavSystem->GetRandomPointInNavigableRadius(NpcLocationOrigin, SearchRadius, NewNpcLocation))
					OwnerComp.GetBlackboardComponent()->SetValueAsVector("PatrolLocation", NewNpcLocation.Location);

				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
