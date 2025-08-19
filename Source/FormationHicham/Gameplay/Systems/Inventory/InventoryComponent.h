// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "InventoryComponent.generated.h"

/**
 * 
 */
template <typename T>
requires std::is_base_of<AActor, T>::value
class FORMATIONHICHAM_API InventoryComponent
{
public:

	bool AddItem(TObjectPtr<T> Item);
	void SwitchItemByID(int32 ItemID);

	TArray<T> GetAllItems();

private:
	
	UPROPERTY()
	TArray<T> Items;

};
