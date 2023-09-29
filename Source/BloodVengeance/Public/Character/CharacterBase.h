#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

class UBVAbilitySystemComponent;
class UBVAttributeSet;
class UAbilitySystemComponent;
class UGameplayAbility;
class AWeapon;

UCLASS()
class BLOODVENGEANCE_API ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACharacterBase();

protected:
	virtual void BeginPlay() override;

protected:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBVAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBVAttributeSet> AttributeSet;

private:

	UPROPERTY(EditAnywhere, Category = "AbilitySystem")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	AWeapon* CurrentWeapon;


public:	

	UFUNCTION(BlueprintCallable)
	UBVAttributeSet* GetAttributeSet() const { return AttributeSet; }

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:

	void AddCharacterAbilities();

public:

	AWeapon* GetCurrentWeapon() { return CurrentWeapon; }
};
