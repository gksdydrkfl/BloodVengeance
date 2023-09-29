#include "Item/Weapon/AnimNotify_NextAttackCheck.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "BloodVengeance/Public/BVGameplayTags.h"

void UAnimNotify_NextAttackCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshComp->GetOwner(), FBVGameplayTags::Get().Montage_NextAttackCheck, FGameplayEventData());
}
