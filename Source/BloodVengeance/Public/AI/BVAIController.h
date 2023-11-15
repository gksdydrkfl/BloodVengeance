#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AI/AIState.h"
#include "BVAIController.generated.h"

class UBlackboardComponent;
class UBehaviorTreeComponent;
class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class UAISenseConfig_Damage;
class UAISenseConfig_Hearing;
struct FAIStimulus;

UCLASS()
class BLOODVENGEANCE_API ABVAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	ABVAIController(const FObjectInitializer& ObjectInitializer);

	virtual void OnPossess(APawn* InPawn) override;

	virtual void BeginPlay() override;

private:

	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorComponent;

	UPROPERTY(EditAnywhere, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UAISenseConfig_Sight> AISight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UAISenseConfig_Damage> AIDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UAISenseConfig_Hearing> AIHearing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = true))
	EAIState EnemyAIState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	AActor* AttackTarget;

public:

	UFUNCTION()
	void OnPerceptionSenceUpdate(const TArray<AActor*>& UpdatedActors);

	bool CanSenceActor(AActor* Actor, const EAISense& InAISence, FAIStimulus& AIStimulus);

	UFUNCTION(BlueprintCallable)
	void SetAIStatePassive(const EAIState& InAIState);
	void SetAIStateAttacking(AActor* SightActor);
	void SetAIStateSight(const EAIState& InAIState, AActor* SightActor);
	void SetAIStateSound(const EAIState& InAIState, const FVector& StimulusLocation);
	void SetAIStateDamage(const EAIState& InAIState);

	void HandleSensedSight(AActor* SightActor);
	void HandleSensedSound(const FVector& StimulusLocation);
	void HandleSensedDamage();

};
