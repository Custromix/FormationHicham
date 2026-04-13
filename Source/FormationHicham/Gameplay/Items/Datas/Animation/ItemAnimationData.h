// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemAnimationData.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class FORMATIONHICHAM_API UItemAnimationData : public UDataAsset
{
	GENERATED_BODY()

public:
	/* Animation Offset */
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Offset)
	FVector PositionOffset;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Offset)
	FRotator RotationOffset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Offset)
	FVector PositionAimOffset;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Offset)
	FRotator RotationAimOffset;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Offset)
	bool bEnableLeftIK;

	/* Animation Character */
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	UAnimSequence* IdlePose;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	UAnimSequence* IdleAimPose;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	UAnimSequence* IdleLoop;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	UAnimSequence* IdleAimLoop;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	UAnimMontage* Fire;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	UAnimMontage* SecondaryFire;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	UAnimSequence* Walk;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	UAnimSequence* WalkAim;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	UAnimSequence* Run;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	UAnimMontage* Reload;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	UAnimSequence* Equip;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	UAnimMontage* Holster;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	UAnimSequence* WallAvoid;

	/* Animation Weapon */
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AnimationWeapon)
	UAnimSequence* WeaponFire;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AnimationWeapon)
	UAnimSequence* WeaponReload;
};
