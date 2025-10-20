// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandomLocation.h"

#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "FormationHicham/Gameplay/Characters/AI/Enemy/TrumpGuardAIController.h"

UBTTask_FindRandomLocation::UBTTask_FindRandomLocation()
{
	NodeName = "FindRandomLocation";
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "ExecutedTASK");

	if (const ATrumpGuardAIController* OwnerAIController = Cast<ATrumpGuardAIController>(OwnerComp.GetAIOwner()))
	{
		if (const APawn* Npc = OwnerAIController->GetPawn())
		{
			const FVector NpcLocationOrigin =  Npc->GetActorLocation();

			if (const UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				FNavLocation NewNpcLocation;
				if (NavSystem->GetRandomPointInNavigableRadius(NpcLocationOrigin, SearchRadius, NewNpcLocation))
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "On met les valeur de loc");
					OwnerComp.GetBlackboardComponent()->SetValueAsVector("PatrolLocation", NewNpcLocation.Location);
				}

				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
