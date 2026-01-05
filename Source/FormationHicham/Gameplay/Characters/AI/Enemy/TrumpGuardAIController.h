// TrumpGuardAIController.h
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TrumpGuardBase.h"
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
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	virtual void OnPossess(APawn* InPawn) override;

public:
	virtual FGenericTeamId GetGenericTeamId() const override { return GenericTeamID; }
	
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

	bool IsPlayerSeen() const { return bIsPlayerSeen; }

	virtual void Tick(float DeltaSeconds) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI|Initialize")
	ATrumpGuardBase* TrumpGuardCharacter;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI|Initialize")
	UAISenseConfig_Sight* SightConfig;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI|Initialize")
	ETeamType TeamID = ETeamType::Enemy;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI|Perception")
	bool bIsPlayerSeen = false;

private:
	UPROPERTY()
	FGenericTeamId GenericTeamID;

	UPROPERTY()
	EAIState CurrentState;

	UPROPERTY()
	UBehaviorTree* BehaviorTree;
};

