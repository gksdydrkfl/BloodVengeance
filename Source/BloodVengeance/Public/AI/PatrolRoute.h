#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PatrolRoute.generated.h"

class USplineComponent;

UCLASS()
class BLOODVENGEANCE_API APatrolRoute : public AActor
{
	GENERATED_BODY()
	
public:	

	APatrolRoute();

protected:
	
	virtual void BeginPlay() override;

private:

	TObjectPtr<USplineComponent> PatrolRoute;

	int32 CurrentIndex;

	int32 Direction;

public:

	UFUNCTION(BlueprintCallable)
	void IncrementPartolRoute();

	UFUNCTION(BlueprintCallable)
	FVector GetPatrolRouteWorldPosition();

};
