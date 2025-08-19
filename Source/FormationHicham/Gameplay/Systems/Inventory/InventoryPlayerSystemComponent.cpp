// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryPlayerSystemComponent.h"

#include "FormationHicham/Gameplay/Items/Weapons/WeaponBase.h"


// Sets default values for this component's properties
UInventoryPlayerSystemComponent::UInventoryPlayerSystemComponent()
{
}


// Called when the game starts
void UInventoryPlayerSystemComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInventoryPlayerSystemComponent::AddItem(TObjectPtr<AItem> Item)
{
	switch (Item.Get()->GetItemType())
	{
	case EItemType::WEAPON:
		{
			AWeaponBase* Weapon = Cast<AWeaponBase>(Item);
			if (WeaponInventoryComponent.Add(Weapon))
				if (!MainItem)MainItem = Weapon;
		
			break;
		}
	
	case EItemType::GRENADE:
		{
			AGrenade* Grenade = Cast<AGrenade>(Item);
			if (GrenadeInventoryComponent.Add(Grenade))
				if (!MainItem) MainItem = Grenade;
		
			break;
		}
	
	case EItemType::AMMO:
		{
			AAmmo* Ammo = Cast<AAmmo>(Item);
			if (AmmoInventoryComponentMap.Contains(Ammo->GetAmmoType()))
				AmmoInventoryComponentMap[Ammo->GetAmmoType()] += Ammo->GetAmmoAmount();
			else
				AmmoInventoryComponentMap.Add(Ammo->GetAmmoType(), Ammo->GetAmmoAmount());

			Ammo->Destroy();
			break;
		}
		
	default:
		break;
		
	}
}

void UInventoryPlayerSystemComponent::SwitchItem(int32 id)
{
	IUsuableInterface* PotentialMainItem = MainItemInventory[id];
	if (MainItem != PotentialMainItem)
		MainItem = PotentialMainItem;
}

void UInventoryPlayerSystemComponent::RemoveItemFromInventory(IUsuableInterface* Item)
{
	if (MainItem == Item)
	{
		MainItem = nullptr;
		MainItemInventory.Remove(Item);
	}
}

