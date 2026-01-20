// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryPlayerSystemComponent.h"

#include "FormationHicham/Gameplay/Items/EItemType.h"
#include "FormationHicham/Gameplay/Items/Weapons/WeaponBase.h"


// Sets default values for this component's properties
UInventoryPlayerSystemComponent::UInventoryPlayerSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UInventoryPlayerSystemComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInventoryPlayerSystemComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FString Debug = FString::Printf(TEXT("Nbr Item : %d\n Current Index : %d\n{"), ItemInventory.Num(), CurrentItemIndex);

	for (int i = 0; i < SwitchList.Num(); i++)
	{
		Debug += FString::Printf(TEXT("\n  Item %d : %s"),i + 1, *SwitchList[i]->ItemName.ToString());
		Debug += FString::Printf(TEXT(" : x %d"), ItemInventory[SwitchList[i]]);
	}
	
	Debug += TEXT("\n}");

	GEngine->AddOnScreenDebugMessage(
		15,
		0.f,
		FColor::Green,
		Debug
	);
}

int UInventoryPlayerSystemComponent::GetNbrItemsByType(const EItemType ItemType)
{
	int NbrItemType = 0;
	
	for (const TPair<TObjectPtr<UItemData>, int32>& Item : ItemInventory)
	{
		if (Item.Value != 0 && Item.Key && Item.Key->ItemType == ItemType)
			NbrItemType++;
	}
	
	return NbrItemType;
}

void UInventoryPlayerSystemComponent::RebuildSwitchList()
{
	SwitchList.Empty();

	// 1. Weapons
	for (const auto& Pair : ItemInventory)
	{
		if (Pair.Key && Pair.Key->ItemType == EItemType::WEAPON)
			SwitchList.Add(Pair.Key);
	}

	// 2. Consumables / Grenades
	for (const auto& Pair : ItemInventory)
	{
		if (Pair.Key && Pair.Key->ItemType == EItemType::CONSUMABLE)
			SwitchList.Add(Pair.Key);
	}

	// 3. Others
	for (const auto& Pair : ItemInventory)
	{
		if (Pair.Key && Pair.Key->ItemType == EItemType::OTHER)
			SwitchList.Add(Pair.Key);
	}

	if (CurrentItemIndex >= SwitchList.Num())
		CurrentItemIndex = INDEX_NONE;
}

bool UInventoryPlayerSystemComponent::RequestAddItem(const TObjectPtr<UItemData>& ItemData)
{
	if (!ItemData)
		return false;
	
	const int NbrOfSpecifiedItem = GetNbrItemsByType(ItemData->ItemType);
	
	switch (ItemData->ItemType)
	{
		case EItemType::WEAPON:
			{
				if (NbrOfSpecifiedItem >= MaxWeapons)
					return false;

				if (ItemInventory.Contains(ItemData))
					return false;

				ItemInventory.Add(ItemData, 1);
				RebuildSwitchList();

				OnItemAdded.Broadcast(ItemData);
				
				return true;
			}
		case EItemType::CONSUMABLE:
			{
				if (NbrOfSpecifiedItem >= MaxConsumable)
					return false;

				if (!ItemData->bIsStackable && ItemInventory.Contains(ItemData))
					return false;

				int32& Quantity = ItemInventory.FindOrAdd(ItemData);
				Quantity++;
				RebuildSwitchList();

				OnItemAdded.Broadcast(ItemData);
				
				return true;
			}
		
		case EItemType::AMMO:
			{
				/*AAmmo* Ammo = Cast<UAmm>(Item);
				if (!Ammo)
					break;
				
				AmmoInventoryMap.FindOrAdd(Ammo->GetAmmoType());
				AmmoInventoryMap[Ammo->GetAmmoType()] += Ammo->GetAmmoAmount();

				Ammo->Destroy();
				break;*/
				RebuildSwitchList();
				return false;
			}
			
		default:
			return false;
	}
}

TObjectPtr<UItemData> UInventoryPlayerSystemComponent::GetCurrentItemData()
{
	if (!SwitchList.IsValidIndex(CurrentItemIndex))
		return nullptr;
	
	return SwitchList[CurrentItemIndex];
}

TObjectPtr<UItemData> UInventoryPlayerSystemComponent::GetNextItemData()
{
	if (!SwitchList.IsValidIndex(CurrentItemIndex))
		return nullptr;
	
	CurrentItemIndex = (CurrentItemIndex + 1) % SwitchList.Num();
	
	return SwitchList[CurrentItemIndex];
}

TObjectPtr<UItemData> UInventoryPlayerSystemComponent::GetPreviousItem()
{
	if (!SwitchList.IsValidIndex(CurrentItemIndex))
		return nullptr;

	CurrentItemIndex = (CurrentItemIndex - 1 + SwitchList.Num()) % SwitchList.Num();
	
	return SwitchList[CurrentItemIndex];
}

void UInventoryPlayerSystemComponent::RemoveItemFromInventory(const TObjectPtr<UItemData>& ItemData)
{
	CurrentItemIndex = 0;
	int32& QuantityLeft = *ItemInventory.Find(ItemData);
	QuantityLeft--;

	if (QuantityLeft <= 0)
		ItemInventory.Remove(ItemData);
	
	RebuildSwitchList();
}

