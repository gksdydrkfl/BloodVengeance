#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "BVAbilitySystemComponent.generated.h"

UCLASS()
class BLOODVENGEANCE_API UBVAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
protected:

	TArray<FGameplayAbilitySpecHandle> InputPressedSpecHandles;

	TArray<FGameplayAbilitySpecHandle> InputReleasedSpecHandles;

	TArray<FGameplayAbilitySpecHandle> InputHeldSpecHandles;

public:

	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);

	void AbilityInputTagPressed(const FGameplayTag& InputTag);

	void AbilityInputTagHeld(const FGameplayTag& InputTag);

	void AbilityInputTagReleased(const FGameplayTag& InputTag);
};

