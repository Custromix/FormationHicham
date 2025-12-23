// TrumpGuard.h
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "FormationHicham/Gameplay/CommonComponents/HealthComponent.h"
#include "FormationHicham/Gameplay/Items/Interface/EnemyInterface.h"
#include "GameFramework/Character.h"
#include "TrumpGuardBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackFinished);

UCLASS(Abstract)
class FORMATIONHICHAM_API ATrumpGuardBase : public ACharacter
{
	GENERATED_BODY()

public:
	ATrumpGuardBase();

public:
	virtual void Tick(float DeltaTime) override;

	UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }

	UFUNCTION(BlueprintCallable, Category = "Attack AI")
	virtual void Attack() {};
	
	UFUNCTION(BlueprintCallable, Category = "Health")
	UHealthComponent* GetHealthComponent() const { return HealthComponent; }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StartMontage();

	void StartMontage_Implementation()
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, "AttacBIEN");

		GetMesh()->GetAnimInstance()->Montage_Play(AttackAnimMontage);
	}
	
	void StopMontage() const { /*GetMesh()->GetAnimInstance()->Montage_Stop(0.2f, AttackAnimMontage);*/ };


protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnDeath() { Destroy(); }

public:
	UPROPERTY(BlueprintCallable, Category = "Attack AI")
	FOnAttackFinished OnAttackFinished;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* AttackAnimMontage;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health", meta=(AllowPrivateAccess="true"))
	UHealthComponent* HealthComponent;
};
