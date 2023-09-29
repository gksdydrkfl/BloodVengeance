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
	
private:

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	FGameplayTag StartupInputTag;

public:

	FGameplayTag GetStartUpInputTag() const { return StartupInputTag; }

};
