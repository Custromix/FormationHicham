// Fill out your copyright notice in the Description page of Project Settings.


#include "HichamCharacter.h"

#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/Engine.h"
#include "FormationHicham/FirstPersonShooterTemplate/FormationHichamCharacter.h"
#include "FormationHicham/Gameplay/Items/Interface/UsuableInterface.h"


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

	Inventory = CreateDefaultSubobject<UInventoryPlayerSystemComponent>(TEXT("Inventory"));
	
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AHichamCharacter::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AHichamCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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
		
		EnhancedPlayerInputComponent->BindAction(SecondUseAction, ETriggerEvent::Started, this, &AHichamCharacter::SecondUse);
		
		EnhancedPlayerInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this, &AHichamCharacter::Reload);

		EnhancedPlayerInputComponent->BindAction(DropAction, ETriggerEvent::Started, this, &AHichamCharacter::DropItem);
		
		EnhancedPlayerInputComponent->BindAction(SwitchItemAction, ETriggerEvent::Started, this, &AHichamCharacter::SwitchItem);
	}else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AHichamCharacter::Move(const FInputActionValue& Value)
{
	FVector2D Movement = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), Movement.X);
		AddMovementInput(GetActorRightVector(), Movement.Y);
	}
}

void AHichamCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxis = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxis.X);
		AddControllerPitchInput(LookAxis.Y);
	}
}

void AHichamCharacter::FirstUse()
{
	Inventory->GetMainItem()->FirstUse(this);
}

void AHichamCharacter::SecondUse()
{
	Inventory->GetMainItem()->SecondUse(this);
}

void AHichamCharacter::Reload()
{
	Inventory->GetMainItem()->ThirdUse(this);
}

void AHichamCharacter::DropItem()
{
	Inventory->GetMainItem()->SecondUse(this);
	Inventory->DropMainItem();
}

void AHichamCharacter::SwitchItem(const FInputActionValue& Value)
{
	Inventory->GetMainItem()->SecondUse(this);
}

// Called every frame
void AHichamCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input


void AHichamCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
										 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
										 bool bFromSweep, const FHitResult& SweepResult)
{
	if (AItem* Item = Cast<AItem>(OtherActor))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, OtherActor->GetName());
		Inventory->AddItem(Item);
		Item->AttachToComponent(CharacterMesh1P, FAttachmentTransformRules::SnapToTargetIncludingScale, "S_Riffle");
		Item->OnGrab();
	}
}
