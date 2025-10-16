// TrumpGuardAIController.h
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FormationHicham/Gameplay/Characters/Enum/ETeam.h"
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
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

public:
	virtual FGenericTeamId GetGenericTeamId() const override { return GenericTeamID; }
	
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	
protected:
	UPROPERTY()
	UAISenseConfig_Sight* SightConfig;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ETeamType TeamID = ETeamType::Enemy;

private:
	UPROPERTY()
	FGenericTeamId GenericTeamID;

};
