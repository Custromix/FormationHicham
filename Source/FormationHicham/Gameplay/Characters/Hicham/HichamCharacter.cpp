// Fill out your copyright notice in the Description page of Project Settings.


#include "HichamCharacter.h"

#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/Engine.h"
#include "FormationHicham/Gameplay/CommonComponents/CharacterMovementComponent/PlayerCharacterMovementComponent.h"
#include "FormationHicham/Gameplay/Items/Melee/Melee.h"
#include "FormationHicham/Gameplay/Items/PickupItem/PickupItem.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values

AHichamCharacter::AHichamCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UPlayerCharacterMovementComponent>(
		ACharacter::CharacterMovementComponentName))
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera World"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = true;
	
	CharacterMesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Character Mesh"));
	CharacterMesh1P->SetupAttachment(Camera);
	
	DropItemLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Drop Item Start"));
	DropItemLocation->SetupAttachment(Camera);

	Inventory = CreateDefaultSubobject<UInventoryPlayerSystemComponent>(TEXT("Inventory"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	
	bUseControllerRotationYaw = true;
}

void AHichamCharacter::OnConstruction(const FTransform& Transform)
{
	SpringArm->SetRelativeLocation(FVector(0, 0, BaseEyeHeight));
	Super::OnConstruction(Transform);
}

bool AHichamCharacter::TryPickupItem(UItemData* Item)
{
	if (!Item)
		return false;
	
	return Inventory->RequestAddItem(Item);
}

// Called when the game starts or when spawned
void AHichamCharacter::BeginPlay()
{
	Super::BeginPlay();
	GenericTeamID = static_cast<uint8>(TeamID);

	Inventory->OnItemAdded.AddDynamic(this, &AHichamCharacter::OnItemAdded);
	StandedEyeHeight = SpringArm->GetComponentLocation().Z;
	CurrentEyeHeight = SpringArm->GetRelativeLocation().Z;
}

void AHichamCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedPlayerInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedPlayerInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AHichamCharacter::Jump);
		
		EnhancedPlayerInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AHichamCharacter::StopJumping);
		
		EnhancedPlayerInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHichamCharacter::Move);

		EnhancedPlayerInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AHichamCharacter::Look);
		
		EnhancedPlayerInputComponent->BindAction(FirstUseAction, ETriggerEvent::Started, this, &AHichamCharacter::FirstUse);
		
		EnhancedPlayerInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &AHichamCharacter::Aim);
		
		EnhancedPlayerInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this, &AHichamCharacter::Reload);

		EnhancedPlayerInputComponent->BindAction(DropAction, ETriggerEvent::Started, this, &AHichamCharacter::DropItem);
		
		EnhancedPlayerInputComponent->BindAction(NextItemAction, ETriggerEvent::Started, this, &AHichamCharacter::NextItem);
		
		EnhancedPlayerInputComponent->BindAction(PreviousItemAction, ETriggerEvent::Started, this, &AHichamCharacter::PreviousItem);
		
		EnhancedPlayerInputComponent->BindAction(CrouchAction, ETriggerEvent::Ongoing, this, &AHichamCharacter::StartCrouch);
		
		EnhancedPlayerInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AHichamCharacter::StopCrouch);
	}
}

void AHichamCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D Movement = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), Movement.X);
		AddMovementInput(GetActorRightVector(), Movement.Y);
	}
}

bool AHichamCharacter::CanJumpInternal_Implementation() const
{
	//return Super::CanJumpInternal_Implementation();
	return JumpIsAllowedInternal();
}

void AHichamCharacter::StartCrouch()
{
	if (!GetCharacterMovement()->IsFalling())
		Crouch();
}

void AHichamCharacter::StopCrouch()
{
	if (GetCharacterMovement()->IsCrouching())
		UnCrouch();
}

void AHichamCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxis = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxis.X);
		AddControllerPitchInput(LookAxis.Y);
	}
}

void AHichamCharacter::OnItemAdded(UItemData* CurrentItemData)
{
	if (!EquippedItemActor)
		Equip(CurrentItemData);
}

void AHichamCharacter::Equip(UItemData* CurrentItemData)
{
	if (!CurrentItemData)
		return;
	
	if (EquippedItemActor)
	{
		EquippedItemActor->Destroy();
		EquippedItemActor = nullptr;
	}
	
	FActorSpawnParameters Params;
	Params.Owner = this;
	
	EquippedItemActor = GetWorld()->SpawnActor<AItem>(CurrentItemData->ItemClass, Params);
	EquippedItemActor->Initialize(CurrentItemData);

	const bool IsAttach = EquippedItemActor->AttachToComponent(CharacterMesh1P, FAttachmentTransformRules::SnapToTargetIncludingScale, CurrentItemData->SocketName);
	FTransform LHIKTransform = GetItemSocketTransformInMeshSpace("LHIK");
	OnItemSwitch.Broadcast(LHIKTransform);
}

void AHichamCharacter::FirstUse()
{
	if (EquippedItemActor && EquippedItemActor->Implements<UUsuableInterface>())
		IUsuableInterface::Execute_Use(EquippedItemActor, Camera);
}

void AHichamCharacter::Aim()
{
	if (!EquippedItemActor && !EquippedItemActor->GetItemData()->bIsAimable)
		return;

	bIsAiming = !bIsAiming;
}

void AHichamCharacter::Reload()
{
	if (EquippedItemActor && EquippedItemActor->Implements<UReloadableInterface>())
		IReloadableInterface::Execute_Reload(EquippedItemActor);
}

void AHichamCharacter::DropItem()
{
	if (!EquippedItemActor)
		return;

	if (!EquippedItemActor->GetItemData()->bIsDroppable)
		return;

	/* Spawn PickupItem */
	FActorSpawnParameters Params;
	Params.Owner = this;
	
	APickupItem* DroppedActor = GetWorld()->SpawnActor<APickupItem>(Params);
	DroppedActor->Initialize(EquippedItemActor->GetItemData());
	DroppedActor->SetActorLocation(DropItemLocation->GetComponentLocation(), false, nullptr, ETeleportType::TeleportPhysics);

	/* Drop PickupItem */
	FVector CameraForwardVector = Camera->GetForwardVector();
	CameraForwardVector.Normalize();
	
	FVector Impulse = CameraForwardVector * DroppingForce;
	DroppedActor->GetSkeletalMesh()->AddImpulse(FVector(Impulse));

	Inventory->RemoveItemFromInventory(Inventory->GetCurrentItemData());

	Equip(Inventory->GetCurrentItemData());
}

void AHichamCharacter::NextItem()
{
	if (!EquippedItemActor)
		return;

	if (Inventory->GetSwitchList().Num() <= 1)
		return;
		
	if (UItemData* NewItemData = Inventory->GetNextItemData())
		Equip(NewItemData);
}

void AHichamCharacter::PreviousItem()
{
	if (!EquippedItemActor)
		return;

	if (Inventory->GetSwitchList().Num() <= 1)
		return;
	
	if (UItemData* NewItemData = Inventory->GetPreviousItem())
		Equip(NewItemData);
}

void AHichamCharacter::OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	Super::OnStartCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
	CurrentEyeHeight = CurrentEyeHeight + HalfHeightAdjust;
	bIsCrouchInterpolating = true;
	CrouchAlpha = 0.f;
	
	CrouchWorldZ = BaseEyeHeight + SpringArm->GetAttachParent()->GetComponentLocation().Z;
}

void AHichamCharacter::OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	Super::OnEndCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
	CurrentEyeHeight = CurrentEyeHeight - HalfHeightAdjust;
	bIsCrouchInterpolating = true;
	CrouchAlpha = 0.f;
}

void AHichamCharacter::Crouch(bool bClientSimulation)
{
	Super::Crouch(bClientSimulation);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Crouch 2");

}

void AHichamCharacter::InterpCrouch(float DeltaTime)
{
	if (!bIsCrouchInterpolating)
		return;
	
	CrouchAlpha += DeltaTime / CrouchDurationS;
	CrouchAlpha = FMath::Clamp(CrouchAlpha, 0.f, 1.f);
	
	float TargetHeight = GetCharacterMovement()->bWantsToCrouch ? BaseEyeHeight + CrouchedEyeHeight: BaseEyeHeight;
	CurrentEyeHeight = FMath::Lerp(CurrentEyeHeight, TargetHeight, CrouchAlpha);
	
	FVector NewVector = FVector(SpringArm->GetRelativeLocation().X, SpringArm->GetRelativeLocation().Y, CurrentEyeHeight);

	SpringArm->SetRelativeLocation(NewVector);
	
	if (CrouchAlpha >= 1.f)
	{
		bIsCrouchInterpolating = false;
		bIsCrouched = false;
	}
}

FTransform AHichamCharacter::GetItemSocketTransformInMeshSpace(const FName SocketName)
{
	if (!EquippedItemActor || !CharacterMesh1P)
		return FTransform::Identity;

	FTransform LHIK = EquippedItemActor->GetSkeletalMesh()->GetSocketTransform(SocketName);

	FVector LHIKLocationInMeshSpace;
	FRotator LHIKRotatorInMeshSpace;
	CharacterMesh1P->TransformToBoneSpace("hand_r", LHIK.GetLocation(), LHIK.Rotator(), LHIKLocationInMeshSpace, LHIKRotatorInMeshSpace);
	
	return FTransform(LHIKRotatorInMeshSpace, LHIKLocationInMeshSpace, FVector::OneVector);
}

// Called every frame
void AHichamCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bIsCrouchInterpolating)
		InterpCrouch(DeltaTime);
}