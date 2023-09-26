#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

class UBVAbilitySystemComponent;
class UBVAttributeSet;
class UAbilitySystemComponent;

UCLASS()
class BLOODVENGEANCE_API ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACharacterBase();

protected:
	virtual void BeginPlay() override;

protected:

	//GameAbilitySystem

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBVAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBVAttributeSet> AttributeSet;


	//GameAbilitySystem

public:	


	UBVAttributeSet* GetAttributeSet() const { return AttributeSet; }

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};
