#include "EnvQueryTest_CoverPoints.h"

#include "Components/CapsuleComponent.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Point.h"

UEnvQueryTest_CoverPoints::UEnvQueryTest_CoverPoints()
{
	Cost = EEnvTestCost::High;
	ValidItemType = UEnvQueryItemType_Point::StaticClass();

	TestPurpose = EEnvTestPurpose::FilterAndScore;
	
	FilterType = EEnvTestFilterType::Match;
}

void UEnvQueryTest_CoverPoints::RunTest(FEnvQueryInstance& QueryInstance) const
{
	UObject* Owner = QueryInstance.Owner.Get();
	if (!Owner) return;

	UWorld* World = Owner->GetWorld();
	if (!World) return;

	APawn* Pawn = Cast<APawn>(Owner);
	if (!Pawn) return;

	const float ActorCapsuleOffset = Pawn->FindComponentByClass<UCapsuleComponent>()->GetScaledCapsuleRadius() * 2 + Offset;

	struct FCornerSign { float X, Y; };
	constexpr FCornerSign CornerSigns[] = { {-1,-1}, {1,-1}, {-1,1}, {1,1} };
	
	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		const FVector Point = GetItemLocation(QueryInstance, It.GetIndex());

		TArray<struct FHitResult> Hit;

		bool bHit = World->SweepMultiByChannel(
			Hit,
			Point,
			Point,
			FQuat::Identity,
			ECC_Visibility,
			FCollisionShape::MakeSphere(SphereRadius)
		);

		if (!bHit)
		{
			It.ForceItemState(EEnvItemStatus::Failed);
			continue;
		}

		TSet<UPrimitiveComponent*> Walls;
		
		for (FHitResult& HitResult : Hit)
		{
			if (HitResult.Component.IsValid() && HitResult.Component->ComponentTags.Contains("World"))
				Walls.Add(HitResult.Component.Get());
		}

		if (Walls.IsEmpty())
		{
			It.ForceItemState(EEnvItemStatus::Failed);
			continue;
		}

		TArray<FVector> CoverPoints;
		for (const UPrimitiveComponent* Wall : Walls)
		{
			FVector Origin, Extent;
			Wall->GetOwner()->GetActorBounds(true, Origin, Extent);

			for (const FCornerSign& Sign : CornerSigns)
			{
				const FVector Corner = FVector(Origin.X + Sign.X * Extent.X, Origin.Y + Sign.Y * Extent.Y, 0.f);
				
				CoverPoints.Add(Corner + FVector(-Sign.X * ActorCapsuleOffset, 0.f, 0.f));
				CoverPoints.Add(Corner + FVector(0.f, -Sign.Y * ActorCapsuleOffset, 0.f));
			}
		}

		// --- Distance minimale du point EQS au cover point le plus proche ---
		float MinDist = FLT_MAX;
		for (const FVector& CoverPoint : CoverPoints)
		{
			DrawDebugPoint(World, CoverPoint, 10.f, FColor::Blue, false, 15.f);

			const float Dist = FVector::Dist2D(Point, CoverPoint);
			UE_LOG(LogTemp, Display, TEXT("Dist: %f"), Dist);
			if (Dist < MinDist)
				MinDist = Dist;
		}

		//UE_LOG(LogTemp, Warning, TEXT("MinDist: %f"), MinDist);
		if (MinDist > CoverLength)
		{
			It.ForceItemState(EEnvItemStatus::Failed);
			continue;
		}
		
		const float Score = 1.f - MinDist / CoverLength;
		UE_LOG(LogTemp, Warning, TEXT("Score: %f"), Score);
		It.SetScore(TestPurpose, FilterType, Score, 0.0f, 1.0f);
	}
}