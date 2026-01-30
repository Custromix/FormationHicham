// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Datas/ItemData.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

enum class EItemType : uint8;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWallCollideOrUncollide, bool, bIsCollide);

UCLASS(Abstract)
class FORMATIONHICHAM_API AItem : public AActor
{
	GENERATED_BODY()

public:
	AItem();
	virtual void Initialize(UItemData* AItemData);

protected:
	virtual void BeginPlay() override;

	UItemData* GetItemData() const { return ItemData; }
	
public:
	void SetActive(bool bChoice);
	bool IsActive() const { return bIsActive; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UItemData* GetItemData() { return ItemData; }
	
	FName GetItemName() const { return ItemName; }

	EItemType GetItemType() const { return ItemType; }

	TObjectPtr<USkeletalMeshComponent> GetSkeletalMesh() const { return ItemMesh; }
	
private:
	bool bIsGoingUp = true;
	FVector StartLocation;
	
	float TempZLocation;
	float TempPitchRotation;

	bool bIsActive = true;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USkeletalMeshComponent* ItemMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UItemData* ItemData;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName ItemName;
	
	EItemType ItemType;

public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnWallCollideOrUncollide OnWallCollideOrUncollide;
};