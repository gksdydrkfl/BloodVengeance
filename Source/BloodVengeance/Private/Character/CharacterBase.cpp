#include "Character/CharacterBase.h"
#include "GAS/BVAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Item/Weapon/Katana/Katana.h"
#include "Item/Weapon/Bow/Bow.h"
#include "Item/Weapon/Arrow/Arrow.h"
#include "GameFramework/CharacterMovementComponent.h"

ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	bIsEquipped = false;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

}

UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}

void ACharacterBase::InitAbilityActorInfo()
{
}

void ACharacterBase::AddCharacterAbilities()
{
	UBVAbilitySystemComponent* ASC = CastChecked<UBVAbilitySystemComponent>(AbilitySystemComponent);
	if (!HasAuthority()) return;

	ASC->AddCharacterAbilities(StartupAbilities);
}

void ACharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, const float& NewLevel) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, NewLevel, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void ACharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultVitalAttirbutes, 1.f);
}

//UAnimMontage* ACharacterBase::GetHitReactMontage_Implementation()
//{
//	return HitReactMontage;
//}

//UAnimMontage* ACharacterBase::GetDeathMontage_Implementation()
//{
//	return DeathMontage;
//}

//UAnimMontage* ACharacterBase::GetDeathMontage()
//{
//	return DeathMontage;
//}


void ACharacterBase::Die()
{
	MulticastHandleDeath();
}

void ACharacterBase::SetADS(const bool& Value)
{
	bIsADS = Value;

	GetCharacterMovement()->bOrientRotationToMovement = !Value;
	if (Value)
	{
		GetCharacterMovement()->MaxWalkSpeed = 150.f;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 600.f;
	}

	bUseControllerRotationYaw = Value;
}

void ACharacterBase::MulticastHandleDeath_Implementation()
{
	/*GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);*/
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACharacterBase::DestroyArrow()
{
	if (Arrow)
	{
		Arrow->Destroy();
		Arrow = nullptr;
	}
}
