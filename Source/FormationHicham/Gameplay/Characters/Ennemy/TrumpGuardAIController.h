// TrumpGuardAIController.h
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "TrumpGuardAIController.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class UBehaviorTree;

UCLASS()
class FORMATIONHICHAM_API ATrumpGuardAIController : public AAIController
{
	GENERATED_BODY()

public:
	ATrumpGuardAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(VisibleAnywhere, Category="AI")
	UAIPerceptionComponent* Perception = nullptr;

	UPROPERTY()
	UAISenseConfig_Sight* SightConfig = nullptr;

	// Option 2 : assigner le BT ici si tu préfères (sinon via le Pawn)
	UPROPERTY(EditDefaultsOnly, Category="AI")
	UBehaviorTree* DefaultBehaviorTree = nullptr;

	UFUNCTION()
	void HandleTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};
