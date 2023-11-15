// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/BVGameplayAbility.h"
#include "ADS.generated.h"

/**
 * 
 */
UCLASS()
class BLOODVENGEANCE_API UADS : public UBVGameplayAbility
{
	GENERATED_BODY()
	
private:

	const float DefaultFieldOfView = 90.f;
	const float ADSFieldOfView = 80.f;
	const FVector DefaultCameraOffset = FVector(0.f, 50.f, 45.f);
	const FVector ADSCameraOffset = FVector(100.f, 70.f, 45.f);


public:

	UFUNCTION(BlueprintCallable)
	void SetADS(bool NewValue);
	UFUNCTION(BlueprintCallable)
	void SetGrabString(bool NewValue);
	UFUNCTION(BlueprintCallable)
	void DestroyArrow();


};
