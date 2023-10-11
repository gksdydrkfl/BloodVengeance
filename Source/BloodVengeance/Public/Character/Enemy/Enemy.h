#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "GameplayEffectTypes.h"
#include "TargetSystem/TargetSystemInterface.h"
#include "Enemy.generated.h"

class UWidgetComponent;

UCLASS()
class BLOODVENGEANCE_API AEnemy : public ACharacterBase, public ITargetSystemInterface
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

private:

	virtual void InitAbilityActorInfo() override;

	void HealthChanged(const FOnAttributeChangeData& Data);

public:

	bool IsTargetable() override;

};
