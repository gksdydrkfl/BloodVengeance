#include "GAS/Abilities/BowBaseAttack.h"
#include "Item/Weapon/Bow/Bow.h"
#include "Item/Weapon/Arrow/Arrow.h"
#include "Character/CharacterBase.h"
#include "Character/AidenCharacter.h"
#include "Player/AidenPlayerController.h"
#include "Kismet/GameplayStatics.h"

#include "BloodVengeance/DebugMacro.h"

void UBowBaseAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

}

void UBowBaseAttack::Shoot()
{
	Bow->SetGrabString(false);

	ACharacterBase* CharacterBase = Cast<ACharacterBase>(GetAvatarActorFromActorInfo());
	if (CharacterBase == nullptr)
	{
		return;
	}

	FDetachmentTransformRules DetachhmentTransformRules(EDetachmentRule::KeepWorld, true);
	AArrow* Arrow = CharacterBase->GetArrow();
	if (Arrow == nullptr)
	{
		return;
	}

	Arrow->DetachFromActor(DetachhmentTransformRules);
	Arrow->SetActive(true);
	CharacterBase->SetArrow(nullptr);


	FVector Start = FVector();
	FVector End = FVector();

	FVector2D ViewportSize;

	if (GEngine)
	{
		GEngine->GameViewport->GetViewportSize(ViewportSize);
		ViewportSize *= 0.5;
	}

	AAidenCharacter* Aiden = Cast<AAidenCharacter>(CharacterBase);
	if (Aiden)
	{
		AAidenPlayerController* AidenPlayerController = Aiden->GetAidenPlayerController();
		if (AidenPlayerController)
		{
			FVector WorldPosition = FVector();
			FVector Direction = FVector();

			bool bScreenToWorld = UGameplayStatics::DeprojectScreenToWorld(AidenPlayerController, ViewportSize, WorldPosition, Direction);
			if (bScreenToWorld)
			{
				if (GetWorld())
				{
					FHitResult HitResult;

					Start = WorldPosition;
					End = Start + (Direction * 2000.f);

					//DRAW_LINE(Start, End);
					bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility);
					if (bHit)
					{
						End = HitResult.ImpactPoint;
					}
				}
				
			}

			Start = Arrow->GetActorLocation();
			Direction = (End - Start).GetSafeNormal();

			//DRAW_LINE(Start, End);
			
			Arrow->SetDirection(Direction, End);
		}
	}
}

ABow* UBowBaseAttack::GetBow()
{
	FGameplayAbilityActorInfo ActorInfo = GetActorInfo();

	AWeapon* Weapon = Cast<ACharacterBase>(ActorInfo.AvatarActor)->GetCurrentWeapon();

	if (Weapon == nullptr)
	{
		return nullptr;
	}

	Bow = Cast<ABow>(Weapon);

	if (Bow == nullptr)
	{
		return nullptr;
	}

	return Bow;
}
