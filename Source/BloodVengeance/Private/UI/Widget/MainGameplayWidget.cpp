#include "UI/Widget/MainGameplayWidget.h"
#include "UI/Widget/CharacterStatusWidget.h"
#include "UI/HUD/CrosshairWidget.h"

void UMainGameplayWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CharacterStatusWidget)
	{
		CharacterStatusWidget->AddToViewport();
	}
	if (CrosshairWidget)
	{
		CrosshairWidget->AddToViewport();
	}
}

void UMainGameplayWidget::UpdateHealthBar(const float& NewValue)
{
	if (CharacterStatusWidget == nullptr)
	{
		return;
	}

	CharacterStatusWidget->UpdateHealthBar(NewValue);
}

void UMainGameplayWidget::UpdateStaminaBar(const float& NewValue)
{
	if (CharacterStatusWidget == nullptr)
	{
		return;
	}

	CharacterStatusWidget->UpdateStaminaBar(NewValue);
}

void UMainGameplayWidget::SetHiddenCrosshair(const bool& NewValue)
{
	if (CrosshairWidget == nullptr)
	{
		return;
	}

	CrosshairWidget->SetHiddenCrosshair(NewValue);
}
