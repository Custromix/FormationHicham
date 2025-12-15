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

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnDeath();

public:
	virtual void Tick(float DeltaTime) override;

	UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }

	UFUNCTION(BlueprintCallable, Category = "Attack AI")
	virtual void Attack() {};

	UFUNCTION(BlueprintCallable, Category = "Attack AI")
	void CallOnAttackFinished() { OnAttackFinished.Broadcast(); }

	UPROPERTY(BlueprintAssignable, Category = "Attack AI")
	FOnAttackFinished OnAttackFinished;
	
	void StartAttackAnim() const;

	UFUNCTION(BlueprintCallable, Category = "Health")
	UHealthComponent* GetHealthComponent() const { return HealthComponent; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimationAsset* AttackAnimMontage;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health", meta=(AllowPrivateAccess="true"))
	UHealthComponent* HealthComponent;
};
