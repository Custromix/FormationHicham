// Fill out your copyright notice in the Description page of Project Settings.


#include "DistanceTrumpGuardAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "FormationHicham/Gameplay/Characters/AI/Enemy/ACharacters/Interfaces/EnemyInterface.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"


// Sets default values
ADistanceTrumpGuardAIController::ADistanceTrumpGuardAIController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADistanceTrumpGuardAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ADistanceTrumpGuardAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (!Blackboard || !Actor) return;

	if (Stimulus.WasSuccessfullySensed())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Joueur aperçu, position mémorisée");

		// On mémorise la position mais PAS le TargetActor
		Target = Actor;
		Blackboard->SetValueAsObject("TargetActor", Actor);
		Blackboard->SetValueAsVector("LastPlayerKnownLocation", Actor->GetActorLocation());
		Blackboard->SetValueAsBool("HasLineOfSight", true);
		Blackboard->SetValueAsBool("bIsOnAlert", true);
		bIsPlayerSeen = true;
		
		TrumpGuard->WhenPlayerSeen();
		SetFocus(Actor);
		
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Joueur perdu de vue");

	// Vérifie si l'acteur est encore vu par une autre source
	FActorPerceptionBlueprintInfo Info;
	PerceptionComponent->GetActorsPerception(Actor, Info);

	const FAISenseID SightID = UAISense_Sight::GetSenseID<UAISense_Sight>();
	bool bStillSeenBySight = false;

	for (const FAIStimulus& S : Info.LastSensedStimuli)
	{
		if (S.Type == SightID && S.WasSuccessfullySensed())
		{
			bStillSeenBySight = true;
			break;
		}
	}

	if (!bStillSeenBySight)
	{
		Blackboard->SetValueAsBool("HasLineOfSight", false);
		bIsPlayerSeen = false;
		Blackboard->SetValueAsVector("LastPlayerKnownLocation", Actor->GetActorLocation());
	}
}

void ADistanceTrumpGuardAIController::OnForgetTarget(AActor* Player)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Joueur oublié, retour patrol");

	Blackboard->ClearValue("LastKnownLocation");
	TrumpGuard->WhenPlayerUnseen();
}

void ADistanceTrumpGuardAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (bIsPlayerSeen)
	{
		if (!Target)
			return;
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Emerald, "change la position");
		Blackboard->SetValueAsVector("LastPlayerKnownLocation", Target->GetActorLocation());
	}
}

