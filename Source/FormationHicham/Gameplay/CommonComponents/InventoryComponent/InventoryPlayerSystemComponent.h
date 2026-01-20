// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FormationHicham/Gameplay/Items/Weapons/WeaponBase.h"
#include "InventoryPlayerSystemComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemAdded, UItemData*, ItemData);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FORMATIONHICHAM_API UInventoryPlayerSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryPlayerSystemComponent();

private:
	int GetNbrItemsByType(EItemType ItemType);
	void RebuildSwitchList();
	
protected:
	virtual void BeginPlay() override;
	
public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	bool RequestAddItem(const TObjectPtr<UItemData>& ItemData);
	void RemoveItemFromInventory(const TObjectPtr<UItemData>& ItemData);

	TArray<TObjectPtr<UItemData>> GetSwitchList() { return SwitchList; }

	TObjectPtr<UItemData> GetCurrentItemData();
	TObjectPtr<UItemData> GetNextItemData();
	TObjectPtr<UItemData> GetPreviousItem();

	FOnItemAdded OnItemAdded;

private:
	
	TMap<TObjectPtr<UItemData>, int32> ItemInventory;
	TMap<EAmmoType, int32> AmmoInventoryMap;

	TArray<TObjectPtr<UItemData>> SwitchList;

	int32 CurrentItemIndex = 0;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Init")
	int MaxWeapons = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Init")
	int MaxConsumable = 4;
	
};
