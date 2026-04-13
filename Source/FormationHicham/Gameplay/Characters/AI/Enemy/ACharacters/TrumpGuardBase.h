// TrumpGuard.h
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Components/WidgetComponent.h"
#include "FormationHicham/Gameplay/CommonComponents/HealthComponent/HealthComponent.h"
#include "GameFramework/Character.h"
#include "TrumpGuardBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttackFinished, ATrumpGuardBase*, Attacker);

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

	void WhenPlayerSeen();
	void WhenPlayerUnseen();

	UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }

	UFUNCTION(BlueprintCallable, Category = "Attack AI")
	virtual void StartAttack() {};
	
	UFUNCTION(BlueprintCallable, Category = "Attack AI")
	virtual void StopAttack() {};
	
	UFUNCTION(BlueprintCallable, Category = "Health")
	UHealthComponent* GetHealthComponent() const { return HealthComponent; }

	void StartMontage() const { GetMesh()->GetAnimInstance()->Montage_Play(AttackAnimMontage); }
	void StopMontage() const { GetMesh()->GetAnimInstance()->Montage_Stop(0.2f, AttackAnimMontage); }

private:
	//static AFormationTestGameState* FormationGameState;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	UWidgetComponent* HealthBar;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	UHealthComponent* HealthComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* AttackAnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float WalkSpeed = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float RunSpeed = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 ScoreAfterKill = 10;

public:
	UPROPERTY(BlueprintCallable, Category = "Attack AI")
	FOnAttackFinished OnAttackFinished;

};
