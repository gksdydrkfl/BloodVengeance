#include "Character/Enemy/EnemyArcher.h"
#include "Item/Weapon/Bow/Bow.h"
#include "BVGameplayTags.h"
#include "GameplayTagContainer.h"

AEnemyArcher::AEnemyArcher()
{
	SetCharacterClass(ECharacterClass::Archer);

	AttackTag.AddTag(FBVGameplayTags::Get().Abilities_BowBaseAttack);

	DefaultAttackRadius = 600.f;

	AttackRadius = 600.f;

	EquipWeaponSocketName = FName("EquipBowSocket");
	UnEquipWeaponSocketName = FName("UnEquipBowSocket");
}

void AEnemyArcher::BeginPlay()
{
	Super::BeginPlay();

	FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
	AWeapon* Weapon = GetWorld()->SpawnActor<ABow>(WeaponClass, FVector::ZeroVector, FRotator::ZeroRotator);
	if (Weapon)
	{
		Weapon->AttachToComponent(GetMesh(), AttachmentTransformRules, FName("Bow_BackTarget"));
	}

	SetCurrentWeapon(Weapon);
}
