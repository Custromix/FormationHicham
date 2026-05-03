// Fill out your copyright notice in the Description page of Project Settings.


#include "HichamCharacter.h"

#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/Engine.h"
#include "FormationHicham/Core/GameMode/FormationTestGameMode.h"
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
	Camera->FieldOfView = FOV;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	
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
	HealthComponent->OnDeath.AddDynamic(this, &AHichamCharacter::OnDeath);
	
	CurrentEyeHeight = SpringArm->GetRelativeLocation().Z;
}

void AHichamCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedPlayerInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedPlayerInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AHichamCharacter::Look);
		
		EnhancedPlayerInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHichamCharacter::Move);
		
		EnhancedPlayerInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AHichamCharacter::StopMove);
		
		EnhancedPlayerInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AHichamCharacter::OnSprint);
		
		EnhancedPlayerInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AHichamCharacter::StopSprint);
		
		EnhancedPlayerInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AHichamCharacter::Jump);
		
		EnhancedPlayerInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AHichamCharacter::StopJumping);
		
		EnhancedPlayerInputComponent->BindAction(CrouchAction, ETriggerEvent::Ongoing, this, &AHichamCharacter::OnCrouch);
		
		EnhancedPlayerInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AHichamCharacter::StopCrouch);
		
		EnhancedPlayerInputComponent->BindAction(FirstUseAction, ETriggerEvent::Triggered, this, &AHichamCharacter::Fire);
		
		EnhancedPlayerInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &AHichamCharacter::SecondaryFire);
		
		EnhancedPlayerInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this, &AHichamCharacter::Reload);

		EnhancedPlayerInputComponent->BindAction(DropAction, ETriggerEvent::Started, this, &AHichamCharacter::DropItem);
		
		EnhancedPlayerInputComponent->BindAction(NextItemAction, ETriggerEvent::Started, this, &AHichamCharacter::NextItem);
		
		EnhancedPlayerInputComponent->BindAction(PreviousItemAction, ETriggerEvent::Started, this, &AHichamCharacter::PreviousItem);
	}
}

void AHichamCharacter::SetupAndStartFovTransition(float NewFOV, float InterpTimeS)
{
	if (!RuntimeFOVCurve)
		RuntimeFOVCurve = NewObject<UCurveFloat>(this, TEXT("Runtime FOV Curve"));
	
	FRichCurve& RichCurve = RuntimeFOVCurve->FloatCurve;
	RichCurve.Reset();
	
	const FKeyHandle K0 = RichCurve.AddKey(0, Camera->FieldOfView);
	const FKeyHandle K1 = RichCurve.AddKey(InterpTimeS, NewFOV);

	RichCurve.SetKeyInterpMode(K0, RCIM_Cubic);
	RichCurve.SetKeyInterpMode(K1, RCIM_Cubic);

	// Tangents auto (optionnel mais souvent souhaité)
	RichCurve.SetKeyTangentMode(K0, RCTM_Auto);
	RichCurve.SetKeyTangentMode(K1, RCTM_Auto);
	
	InterpFOV(RuntimeFOVCurve);
}

void AHichamCharacter::Look(const FInputActionValue& Value)
{
	LookAxis = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxis.X);
		AddControllerPitchInput(LookAxis.Y);
	}
}

void AHichamCharacter::Move(const FInputActionValue& Value)
{
	Movement = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), Movement.X);
		AddMovementInput(GetActorRightVector(), Movement.Y);
	}
}

void AHichamCharacter::StopMove(const FInputActionValue& Value)
{
	Movement = Value.Get<FVector2D>();
}

void AHichamCharacter::OnSprint()
{
	if (IsCrouched() || GetCharacterMovement()->IsFalling() || GetCharacterMovement()->Velocity.Length() <= 0)
		return;
	
	SetupAndStartFovTransition(SprintFOV, InterpFOVTimeS);
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	bIsAiming = false;
	bIsSprinting = true;
}

void AHichamCharacter::StopSprint()
{
	if (!bIsSprinting)
		return;
	SetupAndStartFovTransition(FOV, InterpFOVTimeS);
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	bIsSprinting = false;
}

bool AHichamCharacter::CanJumpInternal_Implementation() const
{
	return JumpIsAllowedInternal();
}

void AHichamCharacter::OnCrouch()
{
	if (!GetCharacterMovement()->IsFalling())
	{
		Crouch();
		StopSprint();
	}
}

void AHichamCharacter::StopCrouch()
{
	if (GetCharacterMovement()->IsCrouching())
		UnCrouch();
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

void AHichamCharacter::Fire()
{
	/*if (bIsSprinting)
		return;*/
	if (!EquippedItemActor)
		return;
	if (!EquippedItemActor->Implements<UFireInterface>())
		return;

	if (IFireInterface::Execute_TryFire(EquippedItemActor, Camera->GetComponentLocation(), Camera->GetForwardVector(), this))
	{
		StopSprint();
		CharacterMesh1P->GetAnimInstance()->Montage_Play(EquippedItemActor->GetItemData()->AnimationData->Fire);
	}
	else
		return; //Play Empty magazine sound
}

void AHichamCharacter::SecondaryFire()
{
	if (!EquippedItemActor || !EquippedItemActor->GetItemData()->bIsAimable || bIsSprinting)
		return;

	bIsAiming = !bIsAiming;

	CharacterMesh1P->GetAnimInstance()->Montage_Play(EquippedItemActor->GetItemData()->AnimationData->SecondaryFire);
}

void AHichamCharacter::Reload()
{
	if (!EquippedItemActor || !EquippedItemActor->Implements<UReloadableInterface>())
		return;

	if (IReloadableInterface::Execute_TryReload(EquippedItemActor))
	{
		OnReload.Broadcast(true);
		CharacterMesh1P->GetAnimInstance()->Montage_Play(EquippedItemActor->GetItemData()->AnimationData->Reload);
	}
}

void AHichamCharacter::EndReload()
{
	OnReload.Broadcast(false);
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
	//FMath::FInterpTo()
	bIsCrouchInterpolating = true;
	CrouchAlpha = 0.f;
}

void AHichamCharacter::OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	Super::OnEndCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
	CurrentEyeHeight = CurrentEyeHeight - HalfHeightAdjust;
	bIsCrouchInterpolating = true;
	CrouchAlpha = 0.f;
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

void AHichamCharacter::OnDeath()
{
	if (AFormationTestGameMode* GM = Cast<AFormationTestGameMode>(GetWorld()->GetAuthGameMode()))
		GM->RequestFinishGame();
	//Destroy();
}

// Called every frame
void AHichamCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bIsFalling = GetCharacterMovement()->IsFalling();
	
	if (bIsCrouchInterpolating)
		InterpCrouch(DeltaTime);
	
}