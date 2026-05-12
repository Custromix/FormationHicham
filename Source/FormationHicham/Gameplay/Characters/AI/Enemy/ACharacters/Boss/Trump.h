// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FormationHicham/Gameplay/Characters/AI/Enemy/ACharacters/Interfaces/EnemyInterface.h"
#include "GameFramework/Character.h"
#include "Trump.generated.h"

UCLASS()
class FORMATIONHICHAM_API ATrump : public ACharacter, public IEnemyInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATrump();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual UBehaviorTree* GetBehaviorTree() override { return BehaviorTree; }

	virtual void WhenPlayerSeen() override;

	virtual void WhenPlayerUnseen() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	UBehaviorTree* BehaviorTree;
};
