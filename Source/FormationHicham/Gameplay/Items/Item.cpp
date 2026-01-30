// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

#include "Components/BoxComponent.h"

// Sets default values
AItem::AItem()
{
	ItemMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	ItemMesh->SetupAttachment(RootComponent);
}

void AItem::Initialize(UItemData* AItemData)
{
	ItemData = AItemData;
	
	ItemMesh->SetSkeletalMesh(ItemData->ItemMesh);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
}

void AItem::SetActive(const bool bChoice)
{
	SetActorHiddenInGame(!bChoice);
	SetActorEnableCollision(bChoice);
	SetActorTickEnabled(bChoice);
	bIsActive = bChoice;
}



