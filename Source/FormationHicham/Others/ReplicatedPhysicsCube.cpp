#include "ReplicatedPhysicsCube.h"
#include "Net/UnrealNetwork.h"

AReplicatedPhysicsCube::AReplicatedPhysicsCube()
{
    // --- Composant Mesh ----------------------------------------------------
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;

    // Les collisions & physique
    Mesh->SetSimulatePhysics(true);
    Mesh->SetNotifyRigidBodyCollision(true);
    Mesh->SetIsReplicated(true);            // important pour répliquer sub-object

    // --- Réplication Actor --------------------------------------------------
    bReplicates = true;                     // réplique cet Actor
    SetReplicateMovement(true);             // réplique transform + vélocité
    bNetLoadOnClient = true;                // autorise le streaming côté client
}

void AReplicatedPhysicsCube::BeginPlay()
{
    Super::BeginPlay();

    // Optionnel : couleur différente si on est serveur ou client (debug)
#if WITH_EDITOR
    if (HasAuthority())
    {
        Mesh->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(1, 0, 0)); // rouge serveur
    }
    else
    {
        Mesh->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(0, 0, 1)); // bleu client
    }
#endif
}

void AReplicatedPhysicsCube::Server_ApplyImpulse_Implementation(const FVector& Impulse,
                                                                const FVector& HitLocation)
{
    if (Mesh && Mesh->IsSimulatingPhysics())
    {
        Mesh->AddImpulseAtLocation(Impulse, HitLocation, TEXT("None"));
    }
}

bool AReplicatedPhysicsCube::Server_ApplyImpulse_Validate(const FVector& Impulse,
                                                          const FVector& HitLocation)
{
    // Ici tu peux vérifier la taille max de l’impulsion, etc.
    return true;
}

void AReplicatedPhysicsCube::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // Si tu avais des variables custom à répliquer -> DOREPLIFETIME(...)
    // Le StaticMeshComponent est déjà marqué replicated via SetIsReplicated(true)
}
