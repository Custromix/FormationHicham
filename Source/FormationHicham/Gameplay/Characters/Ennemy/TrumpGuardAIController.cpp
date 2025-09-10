// TrumpGuardAIController.cpp
#include "TrumpGuardAIController.h"
#include "AIPerceptionComponent.h"
#include "AISenseConfig_Sight.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

ATrumpGuardAIController::ATrumpGuardAIController()
{
    Perception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

    SightConfig->SightRadius = 2000.f;
    SightConfig->LoseSightRadius = 2500.f;
    SightConfig->PeripheralVisionAngleDegrees = 70.f;
    SightConfig->DetectionByAffiliation.bDetectEnemies = true;
    SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
    SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

    Perception->ConfigureSense(*SightConfig);
    Perception->SetDominantSense(SightConfig->GetSenseImplementation());
    Perception->OnTargetPerceptionUpdated.AddDynamic(this, &ATrumpGuardAIController::HandleTargetPerceptionUpdated);
}

void ATrumpGuardAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    // Lance un BehaviorTree si on en a un (depuis le Pawn ou ce contrôleur)
    if (ACharacter* C = Cast<ACharacter>(InPawn))
    {
        // Cherche un BT sur le Pawn (notre champ BehaviorTreeAsset dans ATrumpGuard)
        if (UProperty* Prop = C->GetClass()->FindPropertyByName(TEXT("BehaviorTreeAsset")))
        {
            UBehaviorTree** BTAddr = Prop->ContainerPtrToValuePtr<UBehaviorTree*>(C);
            if (BTAddr && *BTAddr)
            {
                RunBehaviorTree(*BTAddr);
                return;
            }
        }
    }

    if (DefaultBehaviorTree)
    {
        RunBehaviorTree(DefaultBehaviorTree);
    }
}

void ATrumpGuardAIController::HandleTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
    if (UBlackboardComponent* BB = GetBlackboardComponent())
    {
        const FName TargetKey = TEXT("TargetActor");
        if (Stimulus.WasSuccessfullySensed())
        {
            BB->SetValueAsObject(TargetKey, Actor);
        }
        else if (BB->GetValueAsObject(TargetKey) == Actor)
        {
            BB->ClearValue(TargetKey);
        }
    }
}
