// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/KatanaBaseAttack.h"
#include "BloodVengeance/DebugMacro.h"
#include "Item/Weapon/Katana/Katana.h"
#include "Character/CharacterBase.h"
#include "AbilitySystemBlueprintLibrary.h"

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
