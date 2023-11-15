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
class UCommonMontage;
class AArrow;

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

	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeapon>WeaponClass;

private:



	UPROPERTY(EditAnywhere, Category = "AbilitySystem")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TObjectPtr<AWeapon> CurrentWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = true))
	TSubclassOf<UGameplayEffect> DefaultVitalAttirbutes;

	/*UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> HitReactMontage;

	UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimMontage> DeathMontage;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = true))
	bool bIsEquipped;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Montage", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCommonMontage> CommonMontage;

	bool bIsADS;

	TObjectPtr<AArrow> Arrow;


public:

	UFUNCTION(BlueprintCallable)
	UBVAttributeSet* GetAttributeSet() const { return AttributeSet; }

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	FName EquipWeaponSocketName;
	FName UnEquipWeaponSocketName;

protected:

	//어빌리티 시스템
	virtual void InitAbilityActorInfo();
	void AddCharacterAbilities();
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, const float& NewLevel) const;
	virtual void InitializeDefaultAttributes() const;


public:

	AWeapon* GetCurrentWeapon() const { return CurrentWeapon; }

	void SetCurrentWeapon(AWeapon* NewWeapon) { CurrentWeapon = NewWeapon; }

	//virtual UAnimMontage* GetHitReactMontage_Implementation() override;

	//virtual UAnimMontage* GetDeathMontage_Implementation() override;
	/*virtual UAnimMontage* GetDeathMontage();*/

	virtual void Die() override;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastHandleDeath();

	UFUNCTION(BlueprintCallable)
	FName GetEquipWeaponSocketName() const { return EquipWeaponSocketName; }
	UFUNCTION(BlueprintCallable)
	FName GetUnEquipWeaponSocketName() const { return UnEquipWeaponSocketName; }

	UFUNCTION(BlueprintCallable)
	virtual void SetADS(const bool& Value);

	UFUNCTION(BlueprintCallable)
	bool GetADS() const { return bIsADS; }

	void SetArrow(AArrow* NewArrow) { Arrow = NewArrow; }
	AArrow* GetArrow() const { return Arrow; }
	void DestroyArrow();

};
