// Fill out your copyright notice in the Description page of Project Settings.


#include "EnvQueryTest_CloserCorner.h"

#include "EnvironmentQuery/Items/EnvQueryItemType_Point.h"
#include "Materials/MaterialExpressionOperator.h"

UEnvQueryTest_CloserCorner::UEnvQueryTest_CloserCorner()
{
	Cost = EEnvTestCost::Low;
	ValidItemType = UEnvQueryItemType_Point::StaticClass();
}

void UEnvQueryTest_CloserCorner::RunTest(FEnvQueryInstance& QueryInstance) const
{
	UObject* Owner = QueryInstance.Owner.Get();
	if (!Owner) return;

	UWorld* World = Owner->GetWorld();
	if (!World) return;

	TSet<UPrimitiveComponent*> Walls;
	
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

		struct FCornerSign { float X, Y; };
		constexpr FCornerSign CornerSigns[] = { {-1,-1}, {1,-1}, {-1,1}, {1,1} };

		TArray<FVector> Corners;
		for (const UPrimitiveComponent* Wall : Walls)
		{
			FVector Origin, Extent;
			Wall->GetOwner()->GetActorBounds(true, Origin, Extent);

			for (const FCornerSign& Sign : CornerSigns)
			{
				const FVector Corner = FVector(Origin.X + Sign.X * Extent.X, Origin.Y + Sign.Y * Extent.Y, 0.f);
				Corners.Add(Corner);
			}
		}

		float MinDist = FLT_MAX;
		for (const FVector& CoverPoint : Corners)
		{
			DrawDebugPoint(World, CoverPoint, 10.f, FColor::Blue, false, 15.f);

			const float Dist = FVector::Dist2D(Point, CoverPoint);
			UE_LOG(LogTemp, Display, TEXT("Dist: %f"), Dist);
			if (Dist < MinDist)
				MinDist = Dist;
		}

		if (MinDist > CornerLength)
		{
			It.ForceItemState(EEnvItemStatus::Failed);
			continue;
		}
		
		const float Score = 1.f - MinDist / CornerLength;
		UE_LOG(LogTemp, Error, TEXT("Score: %f"), Score);
		It.SetScore(TestPurpose, FilterType, Score, 0.0f, 1.0f);
	}
}
