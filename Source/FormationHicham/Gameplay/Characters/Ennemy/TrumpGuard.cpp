// TrumpGuard.cpp
#include "TrumpGuard.h"
#include "FormationHicham/Gameplay/CommonComponents/HealthComponent.h"
#include "TrumpGuardAIController.h"              // notre contrôleur IA
#include "BehaviorTree/BehaviorTree.h"

ATrumpGuard::ATrumpGuard()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	HealthComponent->OnDeath.AddDynamic(this, &ATrumpGuard::OnDeath);

	// Possession auto par l’IA + contrôleur par défaut
	AutoPossessAI   = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ATrumpGuardAIController::StaticClass();

	// (Optionnel) tu pourras assigner BehaviorTreeAsset dans l’éditeur sur cet acteur
	BehaviorTreeAsset = nullptr;
}

void ATrumpGuard::BeginPlay()
{
	Super::BeginPlay();

	// Si tu préfères lancer le BT depuis le Pawn (sinon on le fait côté Controller)
	if (BehaviorTreeAsset)
	{
		if (AAIController* AIC = Cast<AAIController>(GetController()))
		{
			AIC->RunBehaviorTree(BehaviorTreeAsset);
		}
	}
}

void ATrumpGuard::OnDeath()
{
	Destroy();
}

void ATrumpGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATrumpGuard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
