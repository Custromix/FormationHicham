// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (Owner)
	{
		Owner->SetCanBeDamaged(true);
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	}

	CurrentHealth = MaxHealth;
	
}

void UHealthComponent::Heal(const int Heal)
{
	CurrentHealth = FMath::Clamp(CurrentHealth + Heal, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(CurrentHealth);
}


void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	CurrentHealth -= Damage;
	OnHealthChanged.Broadcast(CurrentHealth);
	if (CurrentHealth <= 0.0f) OnDeath.Broadcast();
}
