// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupItem.h"

#include "FormationHicham/Gameplay/Characters/Player/Hicham/HichamCharacter.h"


// Sets default values
APickupItem::APickupItem()
{
	//PrimaryActorTick.bCanEverTick = true;
	ItemMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Item Mesh"));
	ItemMesh->SetupAttachment(RootComponent);
	ItemMesh->SetGenerateOverlapEvents(true); //Active les events de collision
	/* Active les collision */
	ItemMesh->SetSimulatePhysics(true);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ItemMesh->SetCollisionResponseToAllChannels(ECR_Block);
	ItemMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void APickupItem::Initialize(UItemData* Data)
{
	ItemData = Data;
	ItemMesh->SetSkeletalMesh(ItemData->ItemMesh);
	ItemMesh->SetSimulatePhysics(true);
	const int32 MaterialsNum = ItemMesh->GetMaterials().Num();
	for (int i = 0; i < MaterialsNum; ++i)
	{
		UMaterialInstanceDynamic* NewDynamicMaterialInstance = ItemMesh->CreateDynamicMaterialInstance(i, ItemMesh->GetMaterials()[i]);
		NewDynamicMaterialInstance->SetScalarParameterValue(ClippingParameterName, 0.f);
	}
}

// Called when the game starts or when spawned
void APickupItem::BeginPlay()
{
	Super::BeginPlay();
	ItemMesh->OnComponentHit.AddDynamic(this, &APickupItem::OnHit);
	ItemMesh->OnComponentBeginOverlap.AddDynamic(this, &APickupItem::OnBeginOverlap);
}

void APickupItem::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AHichamCharacter* Character = Cast<AHichamCharacter>(OtherActor);

	if (!Character)
		return;
	
	if (Character->TryPickupItem(ItemData))
		Destroy();
}

void APickupItem::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	AHichamCharacter* Character = Cast<AHichamCharacter>(OtherActor);
	
	if (!Character)
		return;
	
	if (Character->TryPickupItem(ItemData))
		Destroy();
}


/*void APickupItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

//Up & Down + Rotation Idle Animation
	if (Status == EItemStatus::NONE)
	{
		//Rotation calcul
		TempPitchRotation =- 1;
		FRotator Rotation = FRotator3d(0, TempPitchRotation, 0);

		//Location Calcul
		if (bIsGoingUp)
		{
			TempZLocation += ZSpeed;
			if (TempZLocation >= MaxZLocation)
				bIsGoingUp = false;
		}else
		{
			TempZLocation -= ZSpeed;
			if (TempZLocation <= 0.f)
				bIsGoingUp = true;
		}
		
		FVector Location = StartLocation + FVector(0,0, TempZLocation);
		SetActorLocationAndRotation(Location, GetActorRotation() + Rotation);
	}
	
}*/

