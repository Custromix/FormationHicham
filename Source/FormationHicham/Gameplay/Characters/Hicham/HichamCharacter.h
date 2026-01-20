// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "InputAction.h"
#include "Camera/CameraComponent.h"
#include "FormationHicham/Gameplay/Characters/Enum/ETeam.h"
#include "FormationHicham/Gameplay/CommonComponents/HealthComponent/HealthComponent.h"
#include "FormationHicham/Gameplay/CommonComponents/InventoryComponent/InventoryPlayerSystemComponent.h"
#include "GameFramework/Character.h"
#include "HichamCharacter.generated.h"

UCLASS()
class FORMATIONHICHAM_API AHichamCharacter : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHichamCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	UFUNCTION()
	void OnItemAdded(UItemData* CurrentItemData);
	
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void Equip(UItemData* CurrentItemData);
	void FirstUse();
	void Aim();
	void Reload();
	void DropItem();
	void NextItem();
	void PreviousItem();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool TryPickupItem(UItemData* Item);
	
	virtual FGenericTeamId GetGenericTeamId() const override { return GenericTeamID; }
	
protected:
	/* Player Stuff */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Global")
	USceneComponent* Pivot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh)
	USkeletalMeshComponent* CharacterMesh1P;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* Camera;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Health)
	UHealthComponent* HealthComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Inventory)
	UInventoryPlayerSystemComponent* Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	TObjectPtr<AItem> EquippedItemActor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USceneComponent* DropItemLocation;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI")
	ETeamType TeamID = ETeamType::Player;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI")
	float DroppingForce = 1500.f;
	
	#pragma region Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputAction* FirstUseAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputAction* AimAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputAction* ReloadAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputAction* DropAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputAction* NextItemAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputAction* PreviousItemAction;
	#pragma endregion

private:
	UPROPERTY()
	FGenericTeamId GenericTeamID;
};
