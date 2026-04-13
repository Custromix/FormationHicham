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

	//AActor* TrueQueryOwner = Cast<AActor>(QueryInstance.Owner.Get());
	//UE_CVLOG(GET_AI_CONFIG_VAR(bAllowControllersAsEQSQuerier) == false && Cast<AController>(QueryOwner) != nullptr, QueryOwner, LogEQS, Warning, TEXT("Using Controller as query's owner is dangerous since Controller's location is usually not what you expect it to be!"));
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, TrueQueryOwner->GetName());
	
	/*auto list = GetWorld()->GetCurrentLevel()->Actors;
	UE_LOG(LogTemp, Warning, TEXT("TEST ACTOR TARGET EQS"));
	for (auto it = list.begin(); it != list.end(); ++it)
	{
		if (APlayerStart *PlayerStart = Cast<APlayerStart>(*it))
		{
			UE_LOG(LogTemp, Warning, TEXT("Player start finnd"));
			UEnvQueryItemType_Actor::SetContextHelper(ContextData, PlayerStart);
		}
	}*/

	
	// Récupérer le world depuis le Querier, pas depuis GetWorld()



	/*
	APlayerController* PC = QueryInstance.World->GetFirstPlayerController();
	if (!PC || !PC->GetPawn()) return;

	UEnvQueryItemType_Actor::SetContextHelper(ContextData, PC->GetPawn());*/

	/*
	auto list2 = GetWorld()->GetCurrentLevel()->Actors;
	UE_LOG(LogTemp, Warning, TEXT("TEST ACTOR TARGET EQS"));
	for (auto it = list2.begin(); it != list2.end(); ++it)
	{
		if (AHichamCharacter *PlayerStart = Cast<AHichamCharacter>(*it))
		{
			//UE_LOG(LogTemp, Warning, TEXT("Player start finnd"));
			UEnvQueryItemType_Actor::SetContextHelper(ContextData, PlayerStart);
			//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, PlayerStart->GetName());
		}
	}*/


	/*UWorld* World = GetWorld();
	if (!World)
		return;
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "World Find");

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!PlayerController)
		return;
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "PlayerController Find");

	
	AActor* Player = PlayerController->GetPawn();
	if (!Player)
		return;

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, Player->GetName());

	UObject* QuerierObject = QueryInstance.Owner.Get();
	if (!QuerierObject) return;

	UWorld* World = QuerierObject->GetWorld();
	if (!World) return;

	APlayerController* PC = World->GetFirstPlayerController();
	if (!PC || !PC->GetPawn()) return;

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, PC->GetPawn()->GetName());
	UEnvQueryItemType_Actor::SetContextHelper(ContextData, PC->GetPawn());
	
	UEnvQueryItemType_Actor::SetContextHelper(ContextData, Player);*/


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
