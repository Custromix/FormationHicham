// Fill out your copyright notice in the Description page of Project Settings.


#include "Trump.h"


// Sets default values
ATrump::ATrump()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATrump::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrump::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATrump::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATrump::WhenPlayerSeen()
{
}

void ATrump::WhenPlayerUnseen()
{
}

