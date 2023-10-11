#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TargetSystemComponent.generated.h"


class UWidgetComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLOODVENGEANCE_API UTargetSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTargetSystemComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	AActor* NearTarget;

	AActor* OwnerActor;

	APlayerController* OwnerController;

	TSubclassOf<AActor> TargetableActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = true))
	TSubclassOf<UUserWidget> LockedOnWidgetClass;

	UWidgetComponent* LockOnWidgetComponent;

	const float TargetMaxDistance = 2000.f;

	const float PitchDistanceCoefficient = -0.2f;

	const float PitchDistanceOffset = 60.f;

	const float PitchMin = -45.f;

	const float PitchMax = -15.f;

	bool bTargetLock;

public:

	void TargetLockOn();

	void TargetLockOff();

	bool GetTargetLock() { return bTargetLock; }

private:

	TArray<AActor*> GetAllActors();

	bool LineTraceForTarget(TArray<AActor*>& HitActors, const AActor* Actor);

	AActor* FindNearTarget(const TArray<AActor*> HitActors);

	float GetDistanceForTarget(AActor* TargetActor);

	void CreateWidgetTargetMark();

	void SetControllerRotation(bool bValue);

	void UpdateControllerRotation();


};
