// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CommonMontage.generated.h"

/**
 * 
 */
UCLASS()
class BLOODVENGEANCE_API UCommonMontage : public UDataAsset
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	UAnimMontage* HitReactMontage;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	UAnimMontage* DeathMontage;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	UAnimMontage* EquipMontage;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	UAnimMontage* UnEquipMontage;

public:

	UFUNCTION(BlueprintCallable)
	UAnimMontage* GetHitReactMontage() const { return HitReactMontage; }
	UFUNCTION(BlueprintCallable)
	UAnimMontage* GetDeathMontage() const { return DeathMontage; }
	UFUNCTION(BlueprintCallable)
	UAnimMontage* GetEquipMontage() const { return EquipMontage; }
	UFUNCTION(BlueprintCallable)
	UAnimMontage* GetUnEquipMontage() const { return UnEquipMontage; }

};
