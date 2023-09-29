// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapon/Katana/Katana.h"

AKatana::AKatana()
{
	CurrentCombo = 0;
	MaxCombo = 3;
}

void AKatana::SetCurrentCombo(int32 NewValue)
{
	CurrentCombo = NewValue;
}


