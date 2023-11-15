#include "Animation/BowAnimInstance.h"
#include "Character/CharacterBase.h"
#include "Item/Weapon/Bow/Bow.h"

UBowAnimInstance::UBowAnimInstance()
{
}

void UBowAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Bow = Cast<ABow>(GetOwningActor());
}

void UBowAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (CharacterBase == nullptr)
	{
		return;
	}
	
	if (Bow == nullptr)
	{
		Bow = Cast<ABow>(GetOwningActor());
	}

	if (Bow == nullptr)
	{
		return;
	}

	RightHandTransform = CharacterBase->GetMesh()->GetSocketTransform(FName("RightHandSocket"));

	bString = Bow->GetGrabString();
}

void UBowAnimInstance::SetCharacterBase(ACharacterBase* NewCharacter)
{
	CharacterBase = NewCharacter;
}
