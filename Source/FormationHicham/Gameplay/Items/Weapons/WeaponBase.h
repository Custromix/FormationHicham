// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponDataAsset.h"
#include "FormationHicham/Gameplay/Items/Item.h"
#include "FormationHicham/Gameplay/Items/Interfaces/UsuableInterface.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UCLASS()
class FORMATIONHICHAM_API AWeaponBase : public AItem
{
	GENERATED_BODY()

public:
	AWeaponBase();

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;
	
	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	TObjectPtr<UWeaponDataAsset> WeaponInfoDataAsset;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
						bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
				  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor);

protected:
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(Category="Weapon")
	virtual void Fire(FVector Start, FVector End);
	
	UFUNCTION(Category="Weapon")
	virtual void Aim();

	UFUNCTION(Category="Weapon")
	virtual void Reload();

	UFUNCTION(Category="Weapon")
	virtual void OnGrab() override;
	
	UFUNCTION(Category="Weapon")
	virtual void Drop(FVector PlayerForwardVector);
	
	UFUNCTION(Server, Unreliable)
	void ServerHandleFire(FVector ViewportSize);

	UFUNCTION(Server, Unreliable)
	void ServerHandleAim();

	UFUNCTION(Server, Unreliable)
	void ServerHandleReload();
	
	UFUNCTION(Server, Unreliable)
	void ServerHandleDrop();

};
