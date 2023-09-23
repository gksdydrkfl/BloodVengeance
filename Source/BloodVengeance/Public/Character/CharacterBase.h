#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

class UAbilitySystemComponent;
class UBVAttributeSet;

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

	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	TObjectPtr<UBVAttributeSet> AttributeSet;


	//GameAbilitySystem

public:	


	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UBVAttributeSet* GetAttributeSet() const { return AttributeSet; }
};
