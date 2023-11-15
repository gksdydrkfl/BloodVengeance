#include "GAS/Abilities/ADS.h"
#include "Item/Weapon/Bow/Bow.h"
#include "Character/CharacterBase.h"
#include "Character/AidenCharacter.h"
#include "Item/Weapon/Arrow/Arrow.h"
#include "Player/AidenPlayerController.h"
#include "UI/HUD/BVMainHUD.h"
#include "UI/Widget/MainGameplayWidget.h"

void UADS::SetADS(bool NewValue)
{
	ACharacterBase* CharacterBase = Cast<ACharacterBase>(GetAvatarActorFromActorInfo());
	if (CharacterBase == nullptr)
	{
		return;
	}

	CharacterBase->SetADS(NewValue);

	AAidenCharacter* Aiden = Cast<AAidenCharacter>(CharacterBase);
	if (Aiden == nullptr)
	{
		return;
	}

	AAidenPlayerController* Controller = Aiden->GetAidenPlayerController();
	if (Controller == nullptr)
	{
		return;
	}

	ABVMainHUD* MainHUD = Controller->GetMainHUD();
	if (MainHUD == nullptr)
	{
		return;
	}

	UMainGameplayWidget* MainGameplayWidget = MainHUD->GetMainGameplayWidget();
	if (MainGameplayWidget == nullptr)
	{
		return;
	}
	if (NewValue)
	{
		Aiden->SetCameraMode(ADSFieldOfView, ADSCameraOffset);
	}
	else
	{
		Aiden->SetCameraMode(DefaultFieldOfView, DefaultCameraOffset);
	}
	MainGameplayWidget->SetHiddenCrosshair(!NewValue);
}

void UADS::SetGrabString(bool NewValue)
{
	ACharacterBase* CharacterBase = Cast<ACharacterBase>(GetAvatarActorFromActorInfo());

	if (CharacterBase == nullptr)
	{
		return;
	}

	AWeapon* Weapon = CharacterBase->GetCurrentWeapon();

	if (Weapon == nullptr)
	{
		return;
	}

	ABow* Bow = Cast<ABow>(Weapon);

	if (Bow == nullptr)
	{
		return;
	}

	Bow->SetGrabString(NewValue);

}

void UADS::DestroyArrow()
{
	AAidenCharacter* Aiden = Cast<AAidenCharacter>(GetAvatarActorFromActorInfo());

	if (Aiden == nullptr)
	{
		return;
	}

	Aiden->DestroyArrow();
}
