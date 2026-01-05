// TrumpGuardAIController.cpp
#include "TrumpGuardAIController.h"

#include "TrumpGuardBase.h"
#include "FormationHicham/Gameplay/Characters/Enum/EAIStates.h"
#include "FormationHicham/Gameplay/Characters/Hicham/HichamCharacter.h"
#include "GameFramework/GameSession.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "FormationHicham/Gameplay/Items/Interface/EnemyInterface.h"
#include "GameFramework/Character.h"

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
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ATrumpGuardAIController::OnTargetPerceptionUpdated);
}

void ATrumpGuardAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (!Blackboard || !Actor) return;

	
	if (Stimulus.WasSuccessfullySensed())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Le joueur est vu");

		Blackboard->SetValueAsObject("TargetActor", Actor);
		bIsPlayerSeen = true;
		TrumpGuardCharacter->WhenPlayerSeen();
		Blackboard->SetValueAsBool("HasLineOfSight", bIsPlayerSeen);
		return;
	}else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Le joueur a disparu");
	}
	
	FActorPerceptionBlueprintInfo Info;
	PerceptionComponent->GetActorsPerception(Actor, Info);

	bool bStillSeenBySight = false;
	int32 i = 0;
	while (!bStillSeenBySight && Info.LastSensedStimuli.Num() > i)
	{
		if (Info.LastSensedStimuli[i].Type == UAISense::GetSenseID(UAISense_Sight::StaticClass())
			&& Info.LastSensedStimuli[i].WasSuccessfullySensed())
			bStillSeenBySight = true;
		
		i++;
	}
	for (const auto& S : Info.LastSensedStimuli)
	{
		if (S.Type == UAISense::GetSenseID(UAISense_Sight::StaticClass())
			&& S.WasSuccessfullySensed())
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
		Blackboard->SetValueAsBool("HasLineOfSight", bIsPlayerSeen);
	}
}

void ATrumpGuardAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

// 	/*if (!GetPawn()) return;
//
// 	FVector Start = GetPawn()->GetActorLocation();
// 	FVector Direction = GetPawn()->GetActorForwardVector();
// 	float Radius = SightConfig->SightRadius;
// 	float Angle = FMath::DegreesToRadians(SightConfig->PeripheralVisionAngleDegrees);
//
// 	DrawDebugCone(
// 		GetWorld(),
// 		Start,
// 		Direction,
// 		Radius,
// 		Angle / 2,
// 		Angle / 2,
// 		32,
// 		FColor::Green,
// 		false,
// 		-1.0f,
// 		0,
// 		1.0f
// 	);*/
}

void ATrumpGuardAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (ATrumpGuardBase* TrumpGuard = Cast<ATrumpGuardBase>(InPawn))
	{
		TrumpGuardCharacter = TrumpGuard;
		if (TrumpGuard->GetBehaviorTree())
		{
			BehaviorTree = TrumpGuard->GetBehaviorTree();
			RunBehaviorTree(BehaviorTree);
		}
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
}


