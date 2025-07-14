#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ReplicatedPhysicsCube.generated.h"

/**
 *  Actor minimal : un StaticMeshComponent physique + réplication mouvement.
 *  - Simule la physique uniquement sur l'instance serveur (autorité)
 *  - Réplique position/rotation/vélocité vers les clients
 *  - Expose une RPC pour appliquer une impulsion
 */
UCLASS()
class FORMATIONHICHAM_API AReplicatedPhysicsCube : public AActor
{
	GENERATED_BODY()

public:
	// --- Ctor & overrides ---------------------------------------------------
	AReplicatedPhysicsCube();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// --- Mesh ---------------------------------------------------------------
	/** StaticMesh de base (visible dans l'éditeur) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Mesh;

	// --- RPC ----------------------------------------------------------------
	/** Appelé par ex. un projectile : applique une impulsion autoritaire */
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_ApplyImpulse(const FVector& Impulse, const FVector& HitLocation);

protected:
	// Exécuté aussi bien sur serveur que sur client une fois la réplication reçue
	virtual void BeginPlay() override;
};
