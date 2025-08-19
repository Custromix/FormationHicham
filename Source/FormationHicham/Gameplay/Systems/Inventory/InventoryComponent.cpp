// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

bool UInventoryComponent::AddItem(TObjectPtr<AItem> Item)
{
	if (WeaponInventoryComponent.Contains(Item.Get()))
	{
		TObjectPtr<AUsuableItem> Usabled = Cast<AUsuableItem>(Item.Get());
		UsuableItems.Add(Usabled);

			
			
		Item->OnGrab();
		return true;
	}
}

bool UInventoryComponent::RemoveUsuableItem(TObjectPtr<AUsuableItem> Item)
{
	if (UsuableItems.Contains(Item))
	{
		if (MainItem == Item)
			MainItem = nullptr;
		
		UsuableItems.Remove(Item);
		return true;
	}
	return false;
}

void UInventoryComponent::SwitchUsuableItemByRef(TObjectPtr<AUsuableItem> Item)
{
	if (MainItem != Item)
		MainItem = Item;
	
}

void UInventoryComponent::SwitchItemByID(const int32 ItemID)
{
	if (MainItem != UsuableItems[ItemID])
		MainItem = UsuableItems[ItemID];
}

TObjectPtr<AItem> UInventoryComponent::GetItemFromAmmoInventory(int32 ItemID)
{
	return AmmoItems[ItemID];
}

TObjectPtr<AUsuableItem> UInventoryComponent::GetUsuableItemFromInventory(const int32 ItemID)
{
	return UsuableItems[ItemID];
}
