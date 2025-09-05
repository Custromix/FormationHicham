// Fill out your copyright notice in the Description page of Project Settings.


#include "TrumpGuard.h"


// Sets default values
ATrumpGuard::ATrumpGuard()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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
}

void ATrumpGuard::OnDeath()
{
	Destroy();
}

// Called every frame
void ATrumpGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


