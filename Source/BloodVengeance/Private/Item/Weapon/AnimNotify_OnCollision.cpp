#include "Item/Weapon/AnimNotify_OnCollision.h"
#include "Character/CharacterBase.h"
#include "Item/Weapon/Katana/Katana.h"

void UAnimNotify_OnCollision::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	ACharacterBase* Character = Cast<ACharacterBase>(MeshComp->GetOwner());
	if (Character)
	{
		AKatana* Katana = Cast<AKatana>(Character->GetCurrentWeapon());
		if (Katana)
		{
			Katana->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		}
	}
}
