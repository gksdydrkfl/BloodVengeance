#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "GameplayEffectTypes.h"
#include "Data/CharacterClassInfo.h"
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

	UPROPERTY(BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = true))
	bool bHitReacting;

	UPROPERTY(BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = true))
	float BaseWalkSpeed = 250.f;

	UPROPERTY(EditAnywhere, Category = "Character Class Defaults", meta = (AllowPrivateAccess = true))
	int32 Level;

	UPROPERTY(EditAnywhere, Category = "Character Class Defaults", meta = (AllowPrivateAccess = true))
	ECharacterClass CharacterClass;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float LifeSpan = 5.f;

	bool bDeath;

protected:

	FDelegateHandle HealthChangedDelegateHandle;

	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
	void DeathTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

private:

	virtual void InitAbilityActorInfo() override;

	virtual void InitializeDefaultAttributes() const override;

	void HealthChanged(const FOnAttributeChangeData& Data);

public:

	bool IsTargetable() override;

	virtual void Die() override;

	UFUNCTION()
	void OnDeathStarted(AActor* NewActor);

};
