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
#include "GameFramework/SpringArmComponent.h"
#include "HichamCharacter.generated.h"

UENUM(BlueprintType, Blueprintable)
enum class EAvoidanceType : uint8
{
	Animation				UMETA(DisplayName = "Animation"),
	IK						UMETA(DisplayName = "IK"),
	SceneComponent2D		UMETA(DisplayName = "Scene Component 2D"),
	MaterialWorldOffset		UMETA(DisplayName = "Material World offset"),
	UE5_5			 		UMETA(DisplayName = "Unreal Engine E5.5")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemSwitch, FTransform, LHIKTransform);
UCLASS()
class FORMATIONHICHAM_API AHichamCharacter : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHichamCharacter(const FObjectInitializer& ObjectInitializer);
	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	/** Look */
	void Look(const FInputActionValue& Value);
	
	/** Move */
	void Move(const FInputActionValue& Value);

	/** Jump */
	virtual bool CanJumpInternal_Implementation() const override;

	/** Crouch */
	void StartCrouch();
	void StopCrouch();
	
	virtual void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	virtual void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	virtual void Crouch(bool bClientSimulation = false) override;
	void InterpCrouch(float DeltaTime);

	/** Inventory */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void Equip(UItemData* CurrentItemData);
	void FirstUse();
	void Aim();
	void Reload();
	void DropItem();
	void NextItem();
	void PreviousItem();
	
	UFUNCTION()
	void OnItemAdded(UItemData* CurrentItemData);
	
	UFUNCTION(BlueprintCallable, Category="Animation")
	FTransform GetItemSocketTransformInMeshSpace(const FName SocketName);

public:
	/** Called every frame */
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool TryPickupItem(UItemData* Item);
	
	virtual FGenericTeamId GetGenericTeamId() const override { return GenericTeamID; }

private:
	UPROPERTY()
	FGenericTeamId GenericTeamID;
	
	float CrouchWorldZ;
	float CurrentEyeHeight;
	float StandingEyeHeight;
	
protected:
	/* Character Settings */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Mesh)
	USkeletalMeshComponent* CharacterMesh1P;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Camera)
	USpringArmComponent* SpringArm;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera)
	UCameraComponent* Camera;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Health)
	UHealthComponent* HealthComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Inventory)
	UInventoryPlayerSystemComponent* Inventory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gameplay)
	TObjectPtr<AItem> EquippedItemActor;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Gameplay)
	USceneComponent* DropItemLocation;

	
	/* Crouch Settings */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Crouch)
	float StandedEyeHeight;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Crouch)
	float CrouchDurationS = 2.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Crouch)
	float CrouchAlpha = 1.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Crouch)
	bool bIsCrouchInterpolating = false;

	
	/* Other Settings */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AI")
	ETeamType TeamID = ETeamType::Player;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AI")
	float DroppingForce = 1500.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item Settings")
	EAvoidanceType AvoidanceType = EAvoidanceType::Animation;

	
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
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputAction* CrouchAction;
	#pragma endregion

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsAiming = false;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnItemSwitch OnItemSwitch;
};
