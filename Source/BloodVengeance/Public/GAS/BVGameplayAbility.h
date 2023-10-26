// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BVGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class BLOODVENGEANCE_API UBVGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	FGameplayTag StartupInputTag;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FScalableFloat Damage;

public:

	FGameplayTag GetStartUpInputTag() const { return StartupInputTag; }

};
