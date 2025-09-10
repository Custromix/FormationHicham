// TrumpGuard.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TrumpGuard.generated.h"

class UHealthComponent;      // fwd declare
class UBehaviorTree;         // fwd declare

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
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health", meta=(AllowPrivateAccess="true"))
	UHealthComponent* HealthComponent;

	// Assignable dans l’éditeur (ou par défaut en C++)
	UPROPERTY(EditDefaultsOnly, Category="AI")
	UBehaviorTree* BehaviorTreeAsset;
};
