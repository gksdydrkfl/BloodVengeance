// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/BVGameplayAbility.h"
#include "KatanaBaseAttack.generated.h"

class AKatana;

UCLASS()
class BLOODVENGEANCE_API UKatanaBaseAttack : public UBVGameplayAbility
{
	GENERATED_BODY()
	
public:

	UKatanaBaseAttack();

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack Properties", meta = (AllowPrivateAccess = true))
	int32 CurrentCombo;

protected:

public:

	UFUNCTION(BlueprintCallable)
	void BaseAttack();

	UFUNCTION(BlueprintCallable)
	void ResetCombo();

private:

	AKatana* GetKatana();
};
