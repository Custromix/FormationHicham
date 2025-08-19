// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponDataAsset.h"
#include "FormationHicham/Gameplay/Items/Item.h"
#include "FormationHicham/Gameplay/Items/Interface/UsuableInterface.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UCLASS()
class FORMATIONHICHAM_API AWeaponBase : public AItem, public IUsuableInterface
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
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UWeaponDataAsset> WeaponInfoDataAsset;

protected:
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void Fire(FVector ViewportSize);

	UFUNCTION(BlueprintCallable, Category="Weapon")
	void Reload();
	
	UFUNCTION(Server, Unreliable)
	void ServerHandleFire(FVector ViewportSize);

	virtual void FirstUse_Implementation(AHichamCharacter* HichamCharacter) override;
	virtual void SecondUse_Implementation(AHichamCharacter* HichamCharacter) override;
	virtual void ThirdUse_Implementation(AHichamCharacter* HichamCharacter) override;
};
