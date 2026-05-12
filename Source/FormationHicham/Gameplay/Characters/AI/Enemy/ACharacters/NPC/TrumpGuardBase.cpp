// TrumpGuard.cpp
#include "TrumpGuardBase.h"

#include "FormationHicham/Core/GameState/FormationTestGameState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

ATrumpGuardBase::ATrumpGuardBase()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("Health Bar");
	HealthBar->SetupAttachment(GetRootComponent());
	
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	HealthComponent->OnDeath.AddDynamic(this, &ATrumpGuardBase::OnDeath);

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ATrumpGuardBase::BeginPlay()
{
	Super::BeginPlay();
}

void ATrumpGuardBase::OnDeath()
{
	AFormationTestGameState* FormationGameState = GetWorld()->GetGameState<AFormationTestGameState>();
	FormationGameState->IncrementScore(ScoreAfterKill);
	
	Destroy();
}

void ATrumpGuardBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!HealthBar)
		return;

	const FVector HealthBarRotator = HealthBar->GetComponentRotation().Vector();
	const FVector CameraRotator = GetWorld()->GetFirstLocalPlayerFromController()->PlayerController->PlayerCameraManager->GetCameraRotation().Vector();

	const FRotator HealthBarRotation = UKismetMathLibrary::FindLookAtRotation(CameraRotator, HealthBarRotator);
	HealthBar->SetWorldRotation(HealthBarRotation);
}

void ATrumpGuardBase::WhenPlayerSeen()
{
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void ATrumpGuardBase::WhenPlayerUnseen()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}


