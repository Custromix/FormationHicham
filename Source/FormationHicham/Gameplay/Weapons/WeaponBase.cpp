// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"

#include "Components/BoxComponent.h"
#include "FormationHicham/Gameplay/Character/HichamCharacter.h"


// Sets default values
AWeaponBase::AWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	RootComponent = SceneRoot;
	
	GrabberCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Grabber Collider"));
	GrabberCollider->SetupAttachment(RootComponent);
	GrabberCollider->OnComponentBeginOverlap.AddDynamic(this, &AWeaponBase::OnOverlapBegin);

	// SkeletalMesh attaché à Root aussi (indépendant de la capsule)
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponBase::Fire(FVector ViewportSize)
{
	ServerHandleFire(ViewportSize);
}

void AWeaponBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
										 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
										 bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, OtherComp->GetOwner()->GetClass()->GetName());
	
	if (OtherActor->IsA(AHichamCharacter::StaticClass()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Overlap detected!"));
	}
}


void AWeaponBase::ServerHandleFire_Implementation(FVector ViewportSize)
{
	FHitResult HitResult;
	FVector Start = ViewportSize;   // Position de départ (souvent la caméra)
	FVector End = ViewportSize;     // Position d’arrivée (Start + direction * distance)

	

	// Et ensuite :

	bool bHit = GetWorld()->LineTraceSingleByChannel(
	HitResult,
	Start,
	End,
	ECC_Visibility
	);
}
