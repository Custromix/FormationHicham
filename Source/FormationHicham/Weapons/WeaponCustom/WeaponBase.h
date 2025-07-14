// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UCLASS()
class FORMATIONHICHAM_API AWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeaponBase();

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* FireMappingContext;

	/** Fire Input Action */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class AFormationHichamProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;
	
	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* GrabberCollider;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void Fire(FVector ViewportSize);
	
	UFUNCTION(Server, Unreliable)
	void ServerHandleFire(FVector ViewportSize);

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
