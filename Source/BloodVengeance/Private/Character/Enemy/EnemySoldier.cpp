#include "Character/Enemy/EnemySoldier.h"
#include "Item/Weapon/Katana/Katana.h"
#include "BVGameplayTags.h"
#include "GameplayTagContainer.h"

AEnemySoldier::AEnemySoldier()
{
	SetCharacterClass(ECharacterClass::Soldier);

	AttackTag.AddTag(FBVGameplayTags::Get().Abilities_KatanaBaseAttack);
	
	AttackRadius = 150.f;

	DefaultAttackRadius = 350.f;

	EquipWeaponSocketName = FName("EquipKatanaSocket");
	UnEquipWeaponSocketName = FName("UnEquipKatanaSocket");
}

void AEnemySoldier::BeginPlay()
{
	Super::BeginPlay();

	FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
	AWeapon* Weapon = GetWorld()->SpawnActor<AKatana>(WeaponClass, FVector::ZeroVector, FRotator::ZeroRotator);
	if (Weapon)
	{
		Weapon->AttachToComponent(GetMesh(), AttachmentTransformRules, FName("WeaponSocket"));
	}

	SetCurrentWeapon(Weapon);
}
