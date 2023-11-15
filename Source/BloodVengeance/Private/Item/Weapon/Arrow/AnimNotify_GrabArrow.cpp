#include "Item/Weapon/Arrow/AnimNotify_GrabArrow.h"
#include "Item/Weapon/Arrow/Arrow.h"
#include "Character/CharacterBase.h"

void UAnimNotify_GrabArrow::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp == nullptr)
	{
		return;
	}

	const FVector NewLocation = MeshComp->GetSocketLocation(FName("ArrowSocket"));

	AArrow* Arrow = nullptr;
	if (ArrowClass)
	{
		Arrow = MeshComp->GetWorld()->SpawnActor<AArrow>(ArrowClass, NewLocation, FRotator::ZeroRotator);
	}

	if (Arrow == nullptr)
	{
		return;
	}

	FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, true);

	Arrow->AttachToComponent(MeshComp, AttachmentTransformRules, FName("ArrowSocket"));

	AActor* Actor = MeshComp->GetOwner();
	if (Actor == nullptr)
	{
		return;
	}

	ACharacterBase* CharacterBase = Cast<ACharacterBase>(Actor);
	if (CharacterBase == nullptr)
	{
		return;
	}

	CharacterBase->SetArrow(Arrow);

}
