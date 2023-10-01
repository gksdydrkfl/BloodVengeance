#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "GameplayEffectTypes.h"
#include "Enemy.generated.h"

class UWidgetComponent;

UCLASS()
class BLOODVENGEANCE_API AEnemy : public ACharacterBase
{
	GENERATED_BODY()

public:

	AEnemy();

	virtual void BeginPlay() override;


private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UWidgetComponent> HealthBar;

protected:

	FDelegateHandle HealthChangedDelegateHandle;
	FDelegateHandle MaxHealthChangedDelegateHandle;

private:

	virtual void InitAbilityActorInfo() override;

	void HealthChanged(const FOnAttributeChangeData& Data);

};
