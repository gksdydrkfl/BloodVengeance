// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Weapon/Weapon.h"
#include "Katana.generated.h"

/**
 * 
 */
UCLASS()
class BLOODVENGEANCE_API AKatana : public AWeapon
{
	GENERATED_BODY()
	
public:

	AKatana();

private:

	int32 CurrentCombo;

	int32 MaxCombo;

public:

	int32 GetCurrentCombo() { return CurrentCombo; }

	int32 GetMaxCombo() { return MaxCombo; }

	void SetCurrentCombo(int32 NewValue);

	void ResetCombo() { CurrentCombo = 0; }

};
