#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/PlayerState.h"
#include "BVPlayerState.generated.h"

class UAbilitySystemComponent;
class UBVAttributeSet;

UCLASS()
class BLOODVENGEANCE_API ABVPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:

	ABVPlayerState();

	virtual void BeginPlay() override;

private:

	//GameAbilitySystem
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UBVAttributeSet> AttributeSet;
	//GameAbilitySystem

protected:

	FDelegateHandle HealthChangedDelegateHandle;
	FDelegateHandle MaxHealthChangedDelegateHandle;
	FDelegateHandle StaminaChangedDelegateHandle;
	FDelegateHandle MaxStaminaChangedDelegateHandle;

public:

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UBVAttributeSet* GetAttributeSet() const { return AttributeSet; }

public:

	float GetHealth() const;
	float GetMaxHealth() const;
	float GetStamina() const;
	float GetMaxStamina() const;

	virtual void HealthChanged(const FOnAttributeChangeData& Data);
	virtual void MaxHealthChanged(const FOnAttributeChangeData& Data);
	virtual void StaminaChanged(const FOnAttributeChangeData& Data);
	virtual void MaxStaminaChanged(const FOnAttributeChangeData& Data);

};
