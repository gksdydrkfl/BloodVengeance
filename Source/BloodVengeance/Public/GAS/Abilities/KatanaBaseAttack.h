#pragma once

#include "CoreMinimal.h"
#include "GAS/BVGameplayAbility.h"
#include "KatanaBaseAttack.generated.h"

class AKatana;
class UGameplayEffect;

UCLASS()
class BLOODVENGEANCE_API UKatanaBaseAttack : public UBVGameplayAbility
{
	GENERATED_BODY()

public:

	UKatanaBaseAttack();

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack Properties", meta = (AllowPrivateAccess = true))
	int32 CurrentCombo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<UGameplayEffect> DamageEffectClass;

protected:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);


public:

	UFUNCTION(BlueprintCallable)
	void BaseAttack();

	UFUNCTION(BlueprintCallable)
	void ResetCombo();

	UFUNCTION(BlueprintCallable)
	void UpdateMotionWarping();

private:

	AKatana* GetKatana();



};
