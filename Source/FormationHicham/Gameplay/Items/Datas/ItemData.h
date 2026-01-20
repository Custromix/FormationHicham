// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemData.generated.h"

enum class EItemType : uint8;
/**
 * 
 */
UCLASS()
class FORMATIONHICHAM_API UItemData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class AItem> ItemClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMesh* ItemMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ItemName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName SocketName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EItemType ItemType;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsStackable = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAudioBus* InitSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAudioBus* SwitchSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsDroppable = true;
};
