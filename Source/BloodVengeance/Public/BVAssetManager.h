// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "BVAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class BLOODVENGEANCE_API UBVAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:

	static UBVAssetManager& Get();

protected:

	virtual void StartInitialLoading() override;
};
