#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_EndAttackCheck.generated.h"

/**
 * 
 */
UCLASS()
class BLOODVENGEANCE_API UAnimNotify_EndAttackCheck : public UAnimNotify
{
	GENERATED_BODY()
	
protected:

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

};
