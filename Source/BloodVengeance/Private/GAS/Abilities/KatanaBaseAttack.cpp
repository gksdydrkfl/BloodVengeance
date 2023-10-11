#include "GAS/Abilities/KatanaBaseAttack.h"
#include "BloodVengeance/DebugMacro.h"
#include "Item/Weapon/Katana/Katana.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Character/AidenCharacter.h"
#include "MotionWarpingComponent.h"
#include "BloodVengeance/DebugMacro.h"
#include "AbilitySystemComponent.h"

UKatanaBaseAttack::UKatanaBaseAttack()
{

}

void UKatanaBaseAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	//TODO 나중에 블루프린트 내용 C++로 다운그레이드

}

void UKatanaBaseAttack::BaseAttack()
{
	AKatana* Katana = GetKatana();

	CurrentCombo = (Katana->GetCurrentCombo() % Katana->GetMaxCombo()) + 1;

	Katana->SetCurrentCombo(CurrentCombo);

	const UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
	const FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), ASC->MakeEffectContext());
	Katana->SetDamageEffectSpecHandle(SpecHandle);
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
		if (AidenCharacter->GetTartgetLock())
		{
			return;
		}

		UMotionWarpingComponent* MotionWarping = AidenCharacter->GetMotionWarping();

		if (MotionWarping)
		{
			FVector LastLocation = AidenCharacter->GetLastMovementInputVector();

			if (LastLocation.IsZero())
			{
				MotionWarping->RemoveWarpTarget(FName("TargetWarp"));
				return;
			}
			const FVector Location = AidenCharacter->GetActorLocation();
			const FVector TargetLocation = (LastLocation.GetSafeNormal() * 150.f) + Location;
			MotionWarping->AddOrUpdateWarpTargetFromLocation(FName("TargetWarp"), TargetLocation);
		}
	}
}
