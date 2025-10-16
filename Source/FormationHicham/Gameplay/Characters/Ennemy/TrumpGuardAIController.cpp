// TrumpGuardAIController.cpp
#include "TrumpGuardAIController.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

ATrumpGuardAIController::ATrumpGuardAIController()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));

	// Dans BasicAIController.cpp constructeur :
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 1200.f;
	SightConfig->PeripheralVisionAngleDegrees = 90.f;
 
	PerceptionComponent->ConfigureSense(*SightConfig);
	PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
	
	GenericTeamID = (uint8)TeamID;
}

void ATrumpGuardAIController::BeginPlay()
{
	PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &ATrumpGuardAIController::OnPerceptionUpdated);
}

void ATrumpGuardAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "L'IA voit le joueur");
}

ETeamAttitude::Type ATrumpGuardAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	
	GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Orange, "In GetTeamAttitudeTowards");
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(&Other);
	if (OtherTeamAgent)
	{
		GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Blue, "OtherTeamAgent = true");
		GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Cyan, FString::Printf(TEXT("Team ID : %d"), OtherTeamAgent->GetGenericTeamId()));
		GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Cyan, FString::Printf(TEXT("Team ID : %d"), (int32) ETeamType::Neutral));
		if (OtherTeamAgent->GetGenericTeamId() == (uint8) ETeamType::Neutral)
		{
			GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Blue, "GetGenericTeamId = Neutral");
			return ETeamAttitude::Neutral;
		}
		
		if (OtherTeamAgent->GetGenericTeamId() != GetGenericTeamId())
		{
			GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, "GetGenericTeamId = Hostile");
			return ETeamAttitude::Hostile;
		}else
		{
			GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Green, "GetGenericTeamId = Friendly");
			return ETeamAttitude::Friendly;
		}
		//return GetGenericTeamId() != OtherTeamAgent->GetGenericTeamId() ? ETeamAttitude::Hostile : ETeamAttitude::Friendly;
	}
	return ETeamAttitude::Neutral;

	/*
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(&Other);
	return OtherTeamAgent ? FGenericTeamId::GetAttitude(GetGenericTeamId(), OtherTeamAgent->GetGenericTeamId())
		: ETeamAttitude::Neutral;
	 */
}


