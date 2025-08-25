// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"

#include "Physics/ImmediatePhysics/ImmediatePhysicsShared/ImmediatePhysicsCore.h"

AWeaponBase::AWeaponBase()
{
	ItemType = EItemType::WEAPON;
	GrabberCollider->OnComponentBeginOverlap.AddDynamic(this, &AWeaponBase::OnOverlapBegin);
}

void AWeaponBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, "caca");
	/*if (OtherComp->ComponentHasTag("Ground"))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Ground");

	}
	if (OverlappedComp->ComponentHasTag("Ground"))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Ground");
		
		if (Status == EStatus::ONGRAB)
		{
			ItemMesh->SetSimulatePhysics(false);
			ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			Status = EStatus::NONE;
		}
	}*/
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

void AWeaponBase::Fire(FVector3d ViewportSize)
{
	ServerHandleFire(ViewportSize);
}

void AWeaponBase::Aim()
{
}

void AWeaponBase::Reload()
{
}

void AWeaponBase::Drop(FVector CameraForwardVector)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Dropped");
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	CameraForwardVector.Normalize();
	FVector Impulse = CameraForwardVector * 2000.f;
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ItemMesh->SetSimulatePhysics(true);
	ItemMesh->AddImpulse(FVector(Impulse));
	OnRelease();
}

void AWeaponBase::ServerHandleFire_Implementation(FVector3d ViewportSize)
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

void AWeaponBase::ServerHandleAim_Implementation()
{
}

void AWeaponBase::ServerHandleReload_Implementation()
{
}

void AWeaponBase::ServerHandleDrop_Implementation()
{
}




