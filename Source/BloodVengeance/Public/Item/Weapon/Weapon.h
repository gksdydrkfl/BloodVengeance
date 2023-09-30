// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Item.h"
#include "Weapon.generated.h"

/**
 * 
 */
UCLASS()
class BLOODVENGEANCE_API AWeapon : public AItem
{
	GENERATED_BODY()
	
private:

	float Damage;

public:

	float GetDamage() { return Damage; }

	void SetDamage(const float& NewDamage) { Damage = NewDamage; }

};
