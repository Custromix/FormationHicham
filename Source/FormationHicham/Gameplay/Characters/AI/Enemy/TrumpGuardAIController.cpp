// TrumpGuardAIController.cpp
#include "TrumpGuardAIController.h"

#include "TrumpGuard.h"
#include "FormationHicham/Gameplay/Characters/Enum/EAIStates.h"
#include "FormationHicham/Gameplay/Characters/Hicham/HichamCharacter.h"
#include "GameFramework/GameSession.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

ATrumpGuardAIController::ATrumpGuardAIController()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 1500.f;
	SightConfig->LoseSightRadius = 1600.f;
	SightConfig->PeripheralVisionAngleDegrees = 90.f;
	SightConfig->SetMaxAge(5.f);
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
	PerceptionComponent->ConfigureSense(*SightConfig);
	PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
}



void ATrumpGuardAIController::BeginPlay()
{
	Super::BeginPlay();
	//PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &ATrumpGuardAIController::OnPerceptionUpdated);
	if (const ATrumpGuard* TrumpGuard = Cast<ATrumpGuard>(GetPawn()))
	{
		if (TrumpGuard->GetBehaviorTree())
		{
			BehaviorTree = TrumpGuard->GetBehaviorTree();
			RunBehaviorTree(BehaviorTree);
			if (Blackboard)
				Blackboard->SetValueAsObject("TargetActor", GetWorld()->GetFirstPlayerController()->GetCharacter());
			
		}
	}
}

void ATrumpGuardAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, "L'ia a vu le joueur");

	for (AActor* const VisibleActor : UpdatedActors)
	{
		if (Blackboard)
			Blackboard->SetValueAsObject("TargetActor", VisibleActor);
	}
	
}



ETeamAttitude::Type ATrumpGuardAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	if (const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(&Other))
	{
		if (OtherTeamAgent->GetGenericTeamId() == static_cast<uint8>(ETeamType::Neutral)) return ETeamAttitude::Neutral;
		return OtherTeamAgent->GetGenericTeamId() != GetGenericTeamId() ? ETeamAttitude::Hostile : ETeamAttitude::Friendly;
	}
	return ETeamAttitude::Neutral;

	/*
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(&Other);
	return OtherTeamAgent ? FGenericTeamId::GetAttitude(GetGenericTeamId(), OtherTeamAgent->GetGenericTeamId())
		: ETeamAttitude::Neutral;
	 */
}


