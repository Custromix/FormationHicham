// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FormationHicham/Gameplay/Items/Item.h"
#include "GrenadeBehaviour/GrenadeBehaviour.h"
#include "Grenade.generated.h"

UCLASS()
class FORMATIONHICHAM_API AGrenade : public AItem, public IUsuableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGrenade();

protected:
	TSubclassOf<UGrenadeBehaviour> GrenadeBehaviorClass;
	TObjectPtr<UGrenadeBehaviour> GrenadeBehaviour;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	TObjectPtr<UGrenadeBehaviour> GetGrenadeBehaviour() { return GrenadeBehaviour; };

	virtual void Tick(float DeltaTime) override;
	

};
