// Fill out your copyright notice in the Description page of Project Settings.


#include "HichamCharacter.h"

#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/Engine.h"
#include "FormationHicham/Gameplay/Items/Melee/Melee.h"
#include "FormationHicham/Gameplay/Items/PickupItem/PickupItem.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AHichamCharacter::AHichamCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Pivot = CreateDefaultSubobject<USceneComponent>(TEXT("Pivot"));
	Pivot->SetupAttachment(GetCapsuleComponent());

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	SpringArm->SetupAttachment(Pivot);
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	
	CharacterMesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh"));
	CharacterMesh1P->SetupAttachment(Pivot);
	
	DropItemLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Drop Item Start"));
	DropItemLocation->SetupAttachment(Camera);

	Inventory = CreateDefaultSubobject<UInventoryPlayerSystemComponent>(TEXT("Inventory"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	
	bUseControllerRotationYaw = true;
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

	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Hello World!");
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
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("Is Attach : %hs"), IsAttach ? "true" : "false"));
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
	
	if (!bIsAiming)
	{
		bIsAiming = true;
	}
	else
	{
		bIsAiming = false;
	}

	
	
	//if (!EquippedItemActor || EquippedItemActor->Implements<UAimableInterface>())
	
	//IAimableInterface::Execute_Aim(EquippedItemActor);
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

	/* Span Item Physically */
	FActorSpawnParameters Params;
	Params.Owner = this;
	
	APickupItem* DroppedActor = GetWorld()->SpawnActor<APickupItem>(Params);
	DroppedActor->Initialize(EquippedItemActor->GetItemData());
	DroppedActor->SetActorLocation(DropItemLocation->GetComponentLocation(), false, nullptr, ETeleportType::TeleportPhysics);

	/* Drop Item */
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
	//Super::Tick(DeltaTime);
	Pivot->SetRelativeRotation(FRotator(GetControlRotation().Pitch, 0, 0));
}
