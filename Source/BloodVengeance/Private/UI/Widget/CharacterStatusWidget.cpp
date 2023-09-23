// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/CharacterStatusWidget.h"
#include "UI/Widget/HealthBarWidget.h"
#include "UI/Widget/StaminaBarWidget.h"
void UCharacterStatusWidget::UpdateHealthBar(const float& NewValue)
{
	HealthBarWidget->UpdateHealthBar(NewValue);
}

void UCharacterStatusWidget::UpdateStaminaBar(const float& NewValue)
{
	StaminaBarWidget->UpdateStaminaBar(NewValue);
}
