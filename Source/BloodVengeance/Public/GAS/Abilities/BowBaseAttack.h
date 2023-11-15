#pragma once

#include "CoreMinimal.h"
#include "GAS/BVGameplayAbility.h"
#include "BowBaseAttack.generated.h"

class ABow;

UCLASS()
class BLOODVENGEANCE_API UBowBaseAttack : public UBVGameplayAbility
{
	GENERATED_BODY()
	
protected:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);

private:

	ABow* Bow;

public:

	UFUNCTION(BlueprintCallable)
	void Shoot();

private:

	UFUNCTION(BlueprintCallable)
	ABow* GetBow();

};
