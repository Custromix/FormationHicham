// TrumpGuardAIController.h
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FormationHicham/Gameplay/Characters/AI/Enemy/ACharacters/TrumpGuardBase.h"
#include "FormationHicham/Gameplay/Characters/Enum/EAIStates.h"
#include "FormationHicham/Gameplay/Characters/Enum/ETeam.h"
#include "Perception/AIPerceptionTypes.h"
#include "TrumpGuardAIControllerBase.generated.h"

class UAISenseConfig_Sight;

UCLASS(Abstract, NotBlueprintable)
class FORMATIONHICHAM_API ATrumpGuardAIControllerBase : public AAIController
{
	GENERATED_BODY()

public:
	explicit ATrumpGuardAIControllerBase();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus) {}

	virtual void OnPossess(APawn* InPawn) override;

public:
	virtual FGenericTeamId GetGenericTeamId() const override { return GenericTeamID; }
	
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

	bool IsPlayerSeen() const { return bIsPlayerSeen; }
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI|Initialize")
	ATrumpGuardBase* TrumpGuardCharacter;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI|Initialize")
	UAISenseConfig_Sight* SightConfig;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI|Initialize")
	ETeamType TeamID = ETeamType::Enemy;
	
	UPROPERTY(BlueprintReadOnly, Category="AI|Initialize")
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AI|Perception")
	bool bIsPlayerSeen = false;

private:
	UPROPERTY()
	FGenericTeamId GenericTeamID;

	UPROPERTY()
	EAIState CurrentState;
};

