#include "GAS/Abilities/KatanaBaseAttack.h"
#include "BloodVengeance/DebugMacro.h"
#include "Item/Weapon/Katana/Katana.h"
#include "Character/CharacterBase.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Character/AidenCharacter.h"
#include "MotionWarpingComponent.h"
#include "BloodVengeance/DebugMacro.h"

UKatanaBaseAttack::UKatanaBaseAttack()
{

}

void UKatanaBaseAttack::BaseAttack()
{
	AKatana* Katana = GetKatana();

	CurrentCombo = (Katana->GetCurrentCombo() % Katana->GetMaxCombo()) + 1;

	Katana->SetCurrentCombo(CurrentCombo);
}

void UKatanaBaseAttack::ResetCombo()
{
	AKatana* Katana = GetKatana();

	Katana->ResetCombo();
}

AKatana* UKatanaBaseAttack::GetKatana()
{
	FGameplayAbilityActorInfo ActorInfo = GetActorInfo();

	AWeapon* Weapon = Cast<ACharacterBase>(ActorInfo.AvatarActor)->GetCurrentWeapon();

	if (Weapon == nullptr)
	{
		return nullptr;
	}

	AKatana* Katana = Cast<AKatana>(Weapon);

	if (Katana == nullptr)
	{
		return nullptr;
	}

	return Katana;
}

void UKatanaBaseAttack::UpdateMotionWarping()
{
	AAidenCharacter* AidenCharacter = Cast<AAidenCharacter>(GetAvatarActorFromActorInfo());

	if (AidenCharacter)
	{
		UMotionWarpingComponent* MotionWarping = AidenCharacter->GetMotionWarping();

		if (MotionWarping)
		{
			FVector LastLocation = AidenCharacter->GetLastMovementInputVector();
			
			if (LastLocation.IsZero())
			{
				MotionWarping->RemoveWarpTarget(FName("TargetWarp"));

				return;
				//LastLocation = AidenCharacter->GetActorForwardVector();
			}

			const FVector Location = AidenCharacter->GetActorLocation();

			const FVector TargetLocation = (LastLocation.GetSafeNormal() * 100.f) + Location;

			Debug::Log(TargetLocation);

			MotionWarping->AddOrUpdateWarpTargetFromLocation(FName("TargetWarp"), TargetLocation);

		}
	}
}
