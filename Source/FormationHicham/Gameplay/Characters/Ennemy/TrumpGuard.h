// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "FormationHicham/Gameplay/CommonComponents/HealthComponent.h"
#include "GameFramework/Character.h"
#include "TrumpGuard.generated.h"

UCLASS()
class FORMATIONHICHAM_API ATrumpGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATrumpGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnDeath();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	UHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, Category="AI")
	UBehaviorTree* BehaviorTreeAsset;
};
