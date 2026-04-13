// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeTrumpGuardAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"


// Sets default values
AMeleeTrumpGuardAIController::AMeleeTrumpGuardAIController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMeleeTrumpGuardAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AMeleeTrumpGuardAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (!Blackboard || !Actor) return;

	if (Stimulus.WasSuccessfullySensed())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Le joueur est vu");
		Blackboard->SetValueAsObject("TargetActor", Actor);
		bIsPlayerSeen = true;
		TrumpGuardCharacter->WhenPlayerSeen();
		Blackboard->SetValueAsBool("HasLineOfSight", true);
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Le joueur a disparu");

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
		Blackboard->ClearValue("TargetActor");
		bIsPlayerSeen = false;
		TrumpGuardCharacter->WhenPlayerUnseen();
		Blackboard->SetValueAsBool("HasLineOfSight", false);
	}
}


