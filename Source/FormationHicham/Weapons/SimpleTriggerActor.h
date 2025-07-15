// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimpleTriggerActor.generated.h"

UCLASS()
class FORMATIONHICHAM_API ASimpleTriggerActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASimpleTriggerActor();

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                        bool bFromSweep, const FHitResult& SweepResult);

public:
    UPROPERTY(VisibleAnywhere)
    class UCapsuleComponent* Capsule;
};
