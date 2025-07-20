// Fill out your copyright notice in the Description page of Project Settings.


#include "HichamCharacter.h"

#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "FormationHicham/FirstPersonShooterTemplate/FormationHichamCharacter.h"
#include "FormationHicham/Gameplay/Weapons/WeaponBase.h"


// Sets default values
AHichamCharacter::AHichamCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetCapsuleComponent());
	Camera->bUsePawnControlRotation = true;

	CharacterMesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh"));
	CharacterMesh1P->SetupAttachment(Camera);

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AHichamCharacter::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AHichamCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHichamCharacter::Move(const FInputActionValue& value)
{
	FVector2D Movement = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), Movement.X);
		AddMovementInput(GetActorRightVector(), Movement.Y);
	}
}

void AHichamCharacter::Look(const FInputActionValue& value)
{
	FVector2D LookAxis = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxis.X);
		AddControllerPitchInput(LookAxis.Y);
	}
}

void AHichamCharacter::Fire()
{
}

// Called every frame
void AHichamCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AHichamCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedPlayerInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedPlayerInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AHichamCharacter::Jump);
		EnhancedPlayerInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AHichamCharacter::StopJumping);
		
		EnhancedPlayerInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHichamCharacter::Move);

		EnhancedPlayerInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AHichamCharacter::Look);
		
		EnhancedPlayerInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &AHichamCharacter::Fire);
	}else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AHichamCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
										 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
										 bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, OtherComp->GetName());
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, OverlappedComp->GetName());

	if (OtherActor->GetClass() == AWeaponBase::StaticClass())
	{
		OtherActor->AttachToComponent(CharacterMesh1P, FAttachmentTransformRules::SnapToTargetIncludingScale, "S_Riffle");
		SwitchItemByRef(OtherActor);
	}
}

bool AHichamCharacter::SwitchItemByRef(AActor* Item)
{
	if (Item->GetClass() == AWeaponBase::StaticClass())
	{
		if (MainItem != Item)
		{
			MainItem = Item;
			return true;
		}
	}
	
	return false;
}

bool AHichamCharacter::SwitchItemByID(const int32 ItemID)
{
	if (Items[ItemID] != MainItem)
	{
		MainItem = Items[ItemID];
		return true;
	}

	return false;
}

AActor* AHichamCharacter::GetItemFromInventory(const int32 ItemID)
{
	return Items[ItemID];
}

AActor* AHichamCharacter::GetMainItem() const
{
	return MainItem;
}
