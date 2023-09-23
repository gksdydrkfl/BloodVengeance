// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/MainGameplayWidget.h"
#include "UI/Widget/CharacterStatusWidget.h"
void UMainGameplayWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CharacterStatusWidget)
	{
		CharacterStatusWidget->AddToViewport();
	}
}

void UMainGameplayWidget::UpdateHealthBar(const float& NewValue)
{
	CharacterStatusWidget->UpdateHealthBar(NewValue);
}

void UMainGameplayWidget::UpdateStaminaBar(const float& NewValue)
{
	CharacterStatusWidget->UpdateStaminaBar(NewValue);
}
