// Fill out your copyright notice in the Description page of Project Settings.


#include "HichamCharacter.h"

#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "FormationHicham/FirstPersonShooterTemplate/FormationHichamCharacter.h"


// Sets default values
AHichamCharacter::AHichamCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetCapsuleComponent());
	Camera->bUsePawnControlRotation = true;

	CharacterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh"));
	CharacterMesh->SetupAttachment(Camera);
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

