// TrumpGuardAIController.h
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "FormationHicham/Gameplay/Characters/Enum/EAIStates.h"
#include "FormationHicham/Gameplay/Characters/Enum/ETeam.h"
#include "TrumpGuardAIController.generated.h"

class UAISenseConfig_Sight;

UCLASS()
class FORMATIONHICHAM_API ATrumpGuardAIController : public AAIController
{
	GENERATED_BODY()

public:
	explicit ATrumpGuardAIController();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

public:
	virtual FGenericTeamId GetGenericTeamId() const override { return GenericTeamID; }
	
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI|Initialize")
	UAISenseConfig_Sight* SightConfig;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI|Initialize")
	ETeamType TeamID = ETeamType::Enemy;

	
private:
	UPROPERTY()
	FGenericTeamId GenericTeamID;

	UPROPERTY()
	EAIState CurrentState;

	UPROPERTY()
	UBehaviorTree* BehaviorTree;
};
