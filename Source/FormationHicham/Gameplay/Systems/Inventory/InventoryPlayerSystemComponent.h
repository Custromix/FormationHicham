// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "Components/ActorComponent.h"
#include "FormationHicham/Gameplay/Items/Grenade/Grenade.h"
#include "FormationHicham/Gameplay/Items/Weapons/WeaponBase.h"
#include "InventoryPlayerSystemComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FORMATIONHICHAM_API UInventoryPlayerSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryPlayerSystemComponent();

	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public :
	IUsuableInterface* GetMainItem() { return MainItem; }
	
	void AddItem(TObjectPtr<AItem> Item);
	void SwitchItem(int32 id);

private:
	
	TArray<IUsuableInterface*> MainItemInventory;
	
	TArray<TObjectPtr<AWeaponBase>> WeaponInventoryComponent;
	TArray<TObjectPtr<AGrenade>> GrenadeInventoryComponent;
	TMap<EAmmoType, int32> AmmoInventoryComponentMap;

	TArray<AItem*> MainInventory;

	IUsuableInterface* MainItem;
};
