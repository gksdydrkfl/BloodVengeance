#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "BTService_FindNearstPlayer.generated.h"

UCLASS()
class BLOODVENGEANCE_API UBTService_FindNearstPlayer : public UBTService_BlueprintBase
{
	GENERATED_BODY()
	
protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess = true))
	FBlackboardKeySelector TargetToFollowSelector;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess = true))
	FBlackboardKeySelector DistanceToTarget;


};
