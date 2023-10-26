#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interface/CombatInterface.h"
#include "CharacterBase.generated.h"

class UBVAbilitySystemComponent;
class UBVAttributeSet;
class UAbilitySystemComponent;
class UGameplayAbility;
class AWeapon;
class UGameplayEffect;

UCLASS()
class BLOODVENGEANCE_API ACharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	ACharacterBase();

protected:
	virtual void BeginPlay() override;

protected:

	UPROPERTY()
	TObjectPtr<UBVAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UBVAttributeSet> AttributeSet;

private:

	UPROPERTY(EditAnywhere, Category = "AbilitySystem")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	AWeapon* CurrentWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = true))
	TSubclassOf<UGameplayEffect> DefaultVitalAttirbutes;

	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> HitReactMontage;

	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> DeathMontage;

public:

	UFUNCTION(BlueprintCallable)
	UBVAttributeSet* GetAttributeSet() const { return AttributeSet; }

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:

	//어빌리티 시스템
	virtual void InitAbilityActorInfo();
	void AddCharacterAbilities();
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, const float& NewLevel) const;
	virtual void InitializeDefaultAttributes() const;

public:

	AWeapon* GetCurrentWeapon() { return CurrentWeapon; }

	void SetCurrentWeapon(AWeapon* NewWeapon) { CurrentWeapon = NewWeapon; }

	virtual UAnimMontage* GetHitReactMontage_Implementation() override;

	//virtual UAnimMontage* GetDeathMontage_Implementation() override;
	virtual UAnimMontage* GetDeathMontage();

	virtual void Die() override;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastHandleDeath();

};
