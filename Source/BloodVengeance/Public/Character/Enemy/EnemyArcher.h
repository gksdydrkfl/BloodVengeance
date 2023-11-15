// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Enemy/Enemy.h"
#include "EnemyArcher.generated.h"

/**
 * 
 */
UCLASS()
class BLOODVENGEANCE_API AEnemyArcher : public AEnemy
{
	GENERATED_BODY()
	
public:

	AEnemyArcher();

	virtual void BeginPlay() override;

private:


public:



};
