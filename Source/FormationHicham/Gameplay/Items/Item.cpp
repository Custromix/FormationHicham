// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

// Sets default values
AItem::AItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need i
	PrimaryActorTick.bCanEverTick = true;
	
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	RootComponent = SceneRoot;
	
	GrabberCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Grabber Collider"));
	GrabberCollider->SetupAttachment(RootComponent);
	GrabberCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	// SkeletalMesh attaché à Root aussi (indépendant de la capsule)
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->SetupAttachment(RootComponent);
}

void AItem::OnGrab()
{
	GrabberCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AItem::OnRelease()
{
	GrabberCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}


