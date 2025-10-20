// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "InputAction.h"
#include "Camera/CameraComponent.h"
#include "FormationHicham/Gameplay/Characters/Enum/ETeam.h"
#include "FormationHicham/Gameplay/CommonComponents/HealthComponent.h"
#include "FormationHicham/Gameplay/Systems/Inventory/InventoryPlayerSystemComponent.h"
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
	void FirstUse();
	void SecondUse();
	void Reload();
	void DropItem();
	void SwitchItem(const FInputActionValue& Value);
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
						bool bFromSweep, const FHitResult& SweepResult);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual FGenericTeamId GetGenericTeamId() const override { return GenericTeamID; }
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh)
	USkeletalMeshComponent* CharacterMesh1P;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Inventory)
	UInventoryPlayerSystemComponent* Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Health)
	UHealthComponent* HealthComponent;

	
	/* Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputAction* FirstUseAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputAction* SecondUseAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputAction* ReloadAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputAction* DropAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputAction* SwitchItemAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI")
	ETeamType TeamID = ETeamType::Player;

private:
	UPROPERTY()
	FGenericTeamId GenericTeamID;
};
