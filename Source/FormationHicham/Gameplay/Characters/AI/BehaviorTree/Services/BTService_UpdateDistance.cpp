// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdateDistance.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTService_UpdateDistance::UBTService_UpdateDistance()
{
	NodeName = TEXT("Update Distance To Target");
	bNotifyTick = true;
	Interval = 0.2f;
}

void UBTService_UpdateDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	
	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();

	if (!BB)
		return;


	if (AActor* TrumpGuard = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(SelfActorKey.SelectedKeyName)))
	{
		if (AActor* Player = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetActorKey.SelectedKeyName)))
		{
			float DistanceBetweenAiAndPlayer = FVector::Distance(TrumpGuard->GetActorLocation(), Player->GetActorLocation());
			BB->SetValueAsFloat(DistanceKey.SelectedKeyName, DistanceBetweenAiAndPlayer);
		}
	}
	
}
