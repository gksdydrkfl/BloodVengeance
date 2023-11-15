#pragma once

#include "CoreMinimal.h"
#include "Character/Enemy/Enemy.h"
#include "EnemySoldier.generated.h"

/**
 * 
 */
UCLASS()
class BLOODVENGEANCE_API AEnemySoldier : public AEnemy
{
	GENERATED_BODY()
	
public:

	AEnemySoldier();

	virtual void BeginPlay() override;

private:

	float MeleeAttackRadius;


};
