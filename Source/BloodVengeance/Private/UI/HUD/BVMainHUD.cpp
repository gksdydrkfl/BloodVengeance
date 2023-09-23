// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/BVMainHUD.h"
#include "UI/Widget/MainGameplayWidget.h"
#include "Player/BVPlayerState.h"
ABVMainHUD::ABVMainHUD()
{
}

void ABVMainHUD::BeginPlay()
{
	Super::BeginPlay();

	//CreateHUDWidget();
}



void ABVMainHUD::CreateHUDWidget()
{
	if (MainGameplayWidgetClass)
	{
		MainGameplayWidget = CreateWidget<UMainGameplayWidget>(GetWorld(), MainGameplayWidgetClass);
		if (MainGameplayWidget)
		{
			MainGameplayWidget->AddToViewport();
		}
	}
}

void ABVMainHUD::UpdateHealthBar(const float& NewValue)
{
	MainGameplayWidget->UpdateHealthBar(NewValue);;
}

void ABVMainHUD::UpdateStaminaBar(const float& NewValue)
{
	MainGameplayWidget->UpdateStaminaBar(NewValue);;
}
