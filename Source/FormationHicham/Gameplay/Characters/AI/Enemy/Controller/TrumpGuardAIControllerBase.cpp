// TrumpGuardAIController.cpp
#include "TrumpGuardAIControllerBase.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BehaviorTree.h"
#include "FormationHicham/Gameplay/Characters/AI/Enemy/ACharacters/Interfaces/EnemyInterface.h"

ATrumpGuardAIControllerBase::ATrumpGuardAIControllerBase()
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

void ATrumpGuardAIControllerBase::BeginPlay()
{
	Super::BeginPlay();
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ATrumpGuardAIControllerBase::OnTargetPerceptionUpdated);
}

void ATrumpGuardAIControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, InPawn->GetName() + ": Possess");

	if (IEnemyInterface* Enemy = Cast<IEnemyInterface>(InPawn))
	{
		TrumpGuard = Enemy;
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TrumpGuard->GetBehaviorTree()->GetName());

		if (TrumpGuard->GetBehaviorTree())
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, Enemy->_getUObject()->GetName());

			BehaviorTree = TrumpGuard->GetBehaviorTree();
			RunBehaviorTree(BehaviorTree);
		}
	}
}

ETeamAttitude::Type ATrumpGuardAIControllerBase::GetTeamAttitudeTowards(const AActor& Other) const
{
	if (const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(&Other))
	{
		if (OtherTeamAgent->GetGenericTeamId() == static_cast<uint8>(ETeamType::Neutral)) return ETeamAttitude::Neutral;
		return OtherTeamAgent->GetGenericTeamId() != GetGenericTeamId() ? ETeamAttitude::Hostile : ETeamAttitude::Friendly;
	}
	return ETeamAttitude::Neutral;
}


