// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainGameplayWidget.generated.h"

class UCharacterStatusWidget;


UCLASS()
class BLOODVENGEANCE_API UMainGameplayWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

private:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCharacterStatusWidget> CharacterStatusWidget;

public:

	void UpdateHealthBar(const float& NewValue);
	void UpdateStaminaBar(const float& NewValue);

};
