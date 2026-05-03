// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FormationHicham/Gameplay/Items/Item.h"
#include "FormationHicham/Gameplay/Items/Datas/WeaponDataAsset.h"
#include "FormationHicham/Gameplay/Items/Interfaces/FireInterface.h"
#include "FormationHicham/Gameplay/Items/Interfaces/ReloadableInterface.h"
#include "FormationHicham/Gameplay/Items/Interfaces/SecondaryFireInterface.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UCLASS()
class FORMATIONHICHAM_API AWeaponBase : public AItem, public IFireInterface, public ISecondaryFireInterface, public IReloadableInterface
{
	GENERATED_BODY()

public:
	AWeaponBase();
	virtual void Initialize(UItemData* AItemData) override;

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(Category="Weapon")
	virtual void Fire(FVector Start, FVector End, AActor* IgnoredActor);
	
	UFUNCTION(Category="Weapon")
	virtual bool TryFire_Implementation(const FVector Location, const FVector ForwardVector, AActor* IgnoredActor = nullptr) override;
	
	UFUNCTION(Category="Weapon")
	virtual bool TrySecondaryFire_Implementation() override;
	
	UFUNCTION(Category="Weapon")
	virtual bool TryReload_Implementation() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TObjectPtr<UWeaponDataAsset> GetDataInfo() { return WeaponInfoDataAsset; }
	
	UFUNCTION(Category="Weapon")
	bool CanReload();

	UFUNCTION(BlueprintCallable, Category="Weapon")
	void Reload();
	
	UFUNCTION(Server, Unreliable)
	void ServerHandleFire(FVector ViewportSize);

	UFUNCTION(Server, Unreliable)
	void ServerHandleAim();

	UFUNCTION(Server, Unreliable)
	void ServerHandleReload();
	
	UFUNCTION(Server, Unreliable)
	void ServerHandleDrop();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	TObjectPtr<UWeaponDataAsset> WeaponInfoDataAsset;
	
	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation = nullptr;
	
	bool bCanFire = true;
	float FireRateSeconds = 0.f;
	float LastTimeAfterFire = 0.f;
};
