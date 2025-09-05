// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

// Sets default values
AItem::AItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need i
	PrimaryActorTick.bCanEverTick = true;
	
	//SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	//GrabberCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Grabber Collider"));
	//RootComponent = GrabberCollider;

	//GrabberCollider->SetupAttachment(RootComponent);
	//GrabberCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	// SkeletalMesh attaché à Root aussi (indépendant de la capsule)
	ItemMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	RootComponent = ItemMesh;
	//ItemMesh->SetupAttachment(RootComponent);

	Status = EStatus::NONE;
}

void AItem::OnGrab()
{
	//GrabberCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Status = EStatus::ONGRAB;
}

void AItem::OnRelease()
{
	//GrabberCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}


