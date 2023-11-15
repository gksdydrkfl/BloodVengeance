#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_GrabArrow.generated.h"

class AArrow;

UCLASS()
class BLOODVENGEANCE_API UAnimNotify_GrabArrow : public UAnimNotify
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<AArrow> ArrowClass;

protected:

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

};
