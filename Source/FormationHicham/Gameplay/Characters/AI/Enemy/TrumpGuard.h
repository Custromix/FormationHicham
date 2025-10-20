// TrumpGuard.h
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "FormationHicham/Gameplay/CommonComponents/HealthComponent.h"
#include "GameFramework/Character.h"
#include "TrumpGuard.generated.h"

UCLASS()
class FORMATIONHICHAM_API ATrumpGuard : public ACharacter
{
	GENERATED_BODY()

public:
	ATrumpGuard();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnDeath();

public:
	virtual void Tick(float DeltaTime) override;

	UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTree;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health", meta=(AllowPrivateAccess="true"))
	UHealthComponent* HealthComponent;
};
