// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BVMainHUD.generated.h"

class UMainGameplayWidget;

UCLASS()
class BLOODVENGEANCE_API ABVMainHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	ABVMainHUD();

protected:

	virtual void BeginPlay();

private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMainGameplayWidget> MainGameplayWidgetClass;

	TObjectPtr<UMainGameplayWidget> MainGameplayWidget;

public:

	void CreateHUDWidget();

	void UpdateHealthBar(const float& NewValue);
	void UpdateStaminaBar(const float& NewValue);

};
