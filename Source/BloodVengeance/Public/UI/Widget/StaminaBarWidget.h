// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StaminaBarWidget.generated.h"

class UProgressBar;

UCLASS()
class BLOODVENGEANCE_API UStaminaBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> StaminaBar;

public:

	void UpdateStaminaBar(const float& NewValue);
};
