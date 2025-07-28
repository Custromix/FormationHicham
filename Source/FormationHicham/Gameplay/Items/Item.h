// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "Interface/UsuableInterface.h"
#include "Item.generated.h"

class AHichamCharacter;
 
UENUM(BlueprintType, Blueprintable)
enum class EItemType : uint8
{
	WEAPON      UMETA(DisplayName = "Weapon"),
	AMMO        UMETA(DisplayName = "Ammo"),
	CONSUMABLE  UMETA(DisplayName = "Consumable"),
};

UCLASS(Abstract)
class FORMATIONHICHAM_API AItem : public AActor, IUsuableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItem();

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* SceneRoot;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCapsuleComponent* GrabberCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* WeaponMesh;
	
	EItemType ItemType;
	
public:
	
	virtual void OnGrab();
	virtual void OnRelease();

	EItemType GetItemType() const { return ItemType; }
};
