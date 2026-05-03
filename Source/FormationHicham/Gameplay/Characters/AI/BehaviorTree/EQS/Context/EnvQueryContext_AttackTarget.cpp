// Fill out your copyright notice in the Description page of Project Settings.


#include "EnvQueryContext_AttackTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Point.h"
#include "FormationHicham/Gameplay/Characters/Player/Hicham/HichamCharacter.h"
#include "GameFramework/PlayerStart.h"

void UEnvQueryContext_AttackTarget::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	auto list = GetWorld()->GetCurrentLevel()->Actors;
	UE_LOG(LogTemp, Warning, TEXT("TEST ACTOR TARGET EQS"));
	for (auto it = list.begin(); it != list.end(); ++it)
	{
		//if (APlayerStart *PlayerStart = Cast<APlayerStart>(*it))
		if (AHichamCharacter *PlayerStart = Cast<AHichamCharacter>(*it))
		{
			UE_LOG(LogTemp, Warning, TEXT("Player start finnd"));
			UEnvQueryItemType_Actor::SetContextHelper(ContextData, PlayerStart);
		}
	}
	
	
	AActor* QuerierActor = Cast<AActor>(QueryInstance.Owner.Get());
	if (!QuerierActor)
		return;

	AAIController* AIController = Cast<AAIController>(QuerierActor->GetInstigatorController());
	if (!AIController)
		AIController = Cast<AAIController>(QuerierActor);

	if (!AIController)
		return;

	UBlackboardComponent* Blackboard = AIController->GetBlackboardComponent();
	if (!Blackboard)
		return;

	FVector LastPlayerKnownLocation = Blackboard->GetValueAsVector(TEXT("LastPlayerKnownLocation"));
	LastPlayerKnownLocation.Z += 160.f;
	
	if (!LastPlayerKnownLocation.IsNearlyZero())
	{
		UEnvQueryItemType_Point::SetContextHelper(ContextData, LastPlayerKnownLocation);
	}
}
