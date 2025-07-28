// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FormationHicham/Gameplay/Items/Item.h"
#include "FormationHicham/Gameplay/Items/Interface/UsuableInterface.h"
#include "UObject/Object.h"
#include "InventoryComponent.generated.h"

/**
 * 
 */
UCLASS()
class FORMATIONHICHAM_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	bool AddItem(TObjectPtr<AItem> Item);
	bool RemoveItem(TObjectPtr<AItem> Item);

	void SwitchItemByRef(AItem* Item);
	void SwitchItemByID(int32 ItemID);
	
	IUsuableInterface* GetItemFromUsuableInventory(int32 ItemID);
	TObjectPtr<AItem> GetItemFromAmmoInventory(int32 ItemID);
	IUsuableInterface* GetMainItem() const;

private:
	UPROPERTY()
	TArray<IUsuableInterface*> UsuableItems;

	UPROPERTY()
	TArray<TObjectPtr<AItem>> AmmoItems;

	UPROPERTY()
	IUsuableInterface* MainItem;
};
