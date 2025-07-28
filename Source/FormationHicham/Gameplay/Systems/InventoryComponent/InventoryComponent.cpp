// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

bool UInventoryComponent::AddItem(TObjectPtr<AItem> Item)
{
	switch (Item.Get()->GetItemType())
	{
		case EItemType::WEAPON:
		case EItemType::CONSUMABLE:
			if (!UsuableItems.Contains(Item.Get()))
			{
				IUsuableInterface* Usabled = Cast<IUsuableInterface>(Item.Get());
				UsuableItems.Add(Usabled);

				if (!MainItem)
					SwitchItemByRef(Item);
			
				Item->OnGrab();
				return true;
			}
			break;

		case EItemType::AMMO:
			// Static Cast to Ammo
			// Add to Ammo Items list

				AmmoItems.Add(Item);
			break;
	
		default:
			return false;
	}
	
	return false ;
}

bool UInventoryComponent::RemoveItem(TObjectPtr<AItem> Item)
{
	if (UsuableItems.Contains(Item))
	{
		if (MainItem == Item.Get())
			MainItem = nullptr;
		
		UsuableItems.Remove(Item);
		return true;
	}
	return false;
}

void UInventoryComponent::SwitchItemByRef(AItem* Item)
{
	if (MainItem != Item)
		MainItem = Item;
	
}

void UInventoryComponent::SwitchItemByID(const int32 ItemID)
{
	if (MainItem != Items[ItemID])
		MainItem = Items[ItemID];
}

AItem* UInventoryComponent::GetItemFromInventory(const int32 ItemID)
{
	return Items[ItemID];
}

AItem* UInventoryComponent::GetMainItem() const
{
	return MainItem;
}