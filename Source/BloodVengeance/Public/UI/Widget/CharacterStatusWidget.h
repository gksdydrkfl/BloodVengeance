// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterStatusWidget.generated.h"

class UHealthBarWidget;
class UStaminaBarWidget;

UCLASS()
class BLOODVENGEANCE_API UCharacterStatusWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHealthBarWidget> HealthBarWidget;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UStaminaBarWidget> StaminaBarWidget;

public:

	void UpdateHealthBar(const float& NewValue);
	void UpdateStaminaBar(const float& NewValue);

};
