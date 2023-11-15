#include "GAS/Abilities/KatanaBaseAttack.h"
#include "BloodVengeance/DebugMacro.h"
#include "Item/Weapon/Katana/Katana.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Character/AidenCharacter.h"
#include "MotionWarpingComponent.h"
#include "BloodVengeance/DebugMacro.h"
#include "AbilitySystemComponent.h"
#include "BVGameplayTags.h"

#include "BloodVengeance/DebugMacro.h"
UKatanaBaseAttack::UKatanaBaseAttack()
{
	Katana = nullptr;
}

void UKatanaBaseAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	//TODO 나중에 블루프린트 내용 C++로 다운그레이드

}

void UKatanaBaseAttack::BaseAttack()
{
	CurrentCombo = (Katana->GetCurrentCombo() % Katana->GetMaxCombo()) + 1;

	Katana->SetCurrentCombo(CurrentCombo);

	const UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
	const FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), ASC->MakeEffectContext());
	
	FBVGameplayTags GameplayTags = FBVGameplayTags::Get();

	const float ScaledDamage = Damage.GetValueAtLevel(CurrentCombo);

	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Damage, ScaledDamage);

	Katana->SetDamageEffectSpecHandle(SpecHandle);
}

void UKatanaBaseAttack::ResetCombo()
{
	Katana = GetKatana();

	if (Katana == nullptr)
	{
		return;
	}

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

	Katana = Cast<AKatana>(Weapon);

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
