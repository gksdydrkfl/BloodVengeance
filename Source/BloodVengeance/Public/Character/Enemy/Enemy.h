#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "GameplayEffectTypes.h"
#include "Data/CharacterClassInfo.h"
#include "TargetSystem/TargetSystemInterface.h"
#include "Enemy.generated.h"

class UWidgetComponent;
class ABVAIController;
class APatrolRoute;
struct FGameplayTagContainer;
class UBehaviorTree;

UCLASS()
class BLOODVENGEANCE_API AEnemy : public ACharacterBase, public ITargetSystemInterface
{
	GENERATED_BODY()

public:

	AEnemy();

	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY(BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = true))
	bool bHitReacting;

	/*UPROPERTY(BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = true))
	float BaseWalkSpeed = 250.f;*/

	UPROPERTY(EditAnywhere, Category = "Character Class Defaults", meta = (AllowPrivateAccess = true))
	int32 Level;

	UPROPERTY(EditAnywhere, Category = "Character Class Defaults", meta = (AllowPrivateAccess = true))
	ECharacterClass CharacterClass;

	UPROPERTY(EditAnywhere, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<ABVAIController> BVAIController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<APatrolRoute> PatrolRoute;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBehaviorTree> EnemyBehaviorTree;

protected:

	float DefaultAttackRadius;

	float AttackRadius;

	FDelegateHandle HealthChangedDelegateHandle;

	FGameplayTagContainer AttackTag;


private:

	virtual void InitAbilityActorInfo() override;

	virtual void InitializeDefaultAttributes() const override;

	void HealthChanged(const FOnAttributeChangeData& Data);

public:

	bool IsTargetable() override;

	virtual void Die() override;

	UFUNCTION()
	void OnDeathStarted(AActor* NewActor);

	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	UFUNCTION(BlueprintCallable)
	void SetMovementSpeed(const EAIMovementState& NewAIState);

	ECharacterClass GetCharacterClass() const { return CharacterClass; }
	void SetCharacterClass(const ECharacterClass& NewCharacterClass) { CharacterClass = NewCharacterClass; }

	float GetDefaultAttackRadius() const { return DefaultAttackRadius; }
	float GetAttackRadius() const { return AttackRadius; }

	UFUNCTION(BlueprintCallable)
	FGameplayTagContainer GetAttackTag() const { return AttackTag; }

	UBehaviorTree* GetEnemyBehaviorTree() const { return EnemyBehaviorTree; }

};

