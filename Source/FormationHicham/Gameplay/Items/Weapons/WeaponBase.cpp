// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"

#include "Engine/DamageEvents.h"

AWeaponBase::AWeaponBase()
{
	ItemType = EItemType::WEAPON;
	//GrabberCollider->OnComponentBeginOverlap.AddDynamic(this, &AWeaponBase::OnOverlapBegin);
	//GrabberCollider->OnComponentEndOverlap.AddDynamic(this, &AWeaponBase::OnOverlapEnd);
	//GrabberCollider->OnComponentBeginOverlap.AddDynamic(this, &AWeaponBase::OnOverlapBegin);
	//ItemMesh->OnComponentHit.AddDynamic(this, &AWeaponBase::OnHit);
}


void AWeaponBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
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

void AWeaponBase::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
				  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AWeaponBase::OnHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor)
{
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

void AWeaponBase::Fire(FVector Start, FVector End)
{
	FHitResult HitResult;
	
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	
	bool bHit = GetWorld()->LineTraceSingleByChannel(
	HitResult,
	Start,
	Start + End * 5000.0f,
	ECC_Visibility
	);
	
	if (bHit)
	{
		DrawDebugLine(GetWorld(), Start, HitResult.Location, FColor::Red, false, 2.0f);
		
		if (WeaponInfoDataAsset->DamageType == EDamageType::POINT)
		{
			FPointDamageEvent DamageType;
			HitResult.GetActor()->TakeDamage(WeaponInfoDataAsset->Damage, DamageType, GetInstigatorController(), GetOwner());
		}else
		{
			FRadialDamageEvent DamageType;
			HitResult.GetActor()->TakeDamage(WeaponInfoDataAsset->Damage, DamageType, GetInstigatorController(), GetOwner());
		}
	}
	else DrawDebugLine(GetWorld(), Start, End, FColor::Blue, false, 2.0f);
}

void AWeaponBase::Aim()
{
}

void AWeaponBase::Reload()
{
}

void AWeaponBase::OnGrab()
{
	Super::OnGrab();
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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




