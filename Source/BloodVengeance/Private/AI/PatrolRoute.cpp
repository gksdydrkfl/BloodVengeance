#include "AI/PatrolRoute.h"
#include "Components/SplineComponent.h"

APatrolRoute::APatrolRoute()
{
	PrimaryActorTick.bCanEverTick = true;

	PatrolRoute = CreateDefaultSubobject<USplineComponent>(TEXT("PatrolRoute"));

	CurrentIndex = 0;

	Direction = 1;
}

void APatrolRoute::BeginPlay()
{
	Super::BeginPlay();
	
}

void APatrolRoute::IncrementPartolRoute()
{
	if (PatrolRoute == nullptr)
	{
		return;
	}


	if (PatrolRoute->GetNumberOfSplinePoints() - 1 == CurrentIndex)
	{
		Direction = -1;
	}
	else
	{
		if (CurrentIndex == 0)
		{
			Direction = 1;
		}
	}

	CurrentIndex += Direction;
}

FVector APatrolRoute::GetPatrolRouteWorldPosition()
{
	if (PatrolRoute == nullptr)
	{
		return FVector();
	}

	return PatrolRoute->GetLocationAtSplinePoint(CurrentIndex, ESplineCoordinateSpace::World);
}
