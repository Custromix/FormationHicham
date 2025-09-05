// Fill out your copyright notice in the Description page of Project Settings.


#include "TrumpGuardAIController.h"


// Sets default values
ATrumpGuardAIController::ATrumpGuardAIController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Perception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

	SightConfig->SightRadius = 2000.f;
	SightConfig->LoseSightRadius = 2500.f;
	SightConfig->PeripheralVisionAngleDegrees = 70.f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	Perception->ConfigureSense(*SightConfig);
	Perception->SetDominantSense(SightConfig->GetSenseImplementation());
	Perception->OnTargetPerceptionUpdated.AddDynamic(this, &ATrumpGuardAIController::HandleTargetPerceptionUpdated);
}

// Called when the game starts or when spawned
void ATrumpGuardAIController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrumpGuardAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

