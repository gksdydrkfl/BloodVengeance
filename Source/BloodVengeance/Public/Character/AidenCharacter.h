#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "AidenCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class AItem;
class UMotionWarpingComponent;
class UTargetSystemComponent;

UCLASS()
class BLOODVENGEANCE_API AAidenCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:

	AAidenCharacter();

	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;

	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent> FollowCamera;



	UPROPERTY(EditAnywhere)
	TSubclassOf<AItem> KatanaClass;

	UMotionWarpingComponent* MotionWarping;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TargetSystem", meta = (AllowPrivateAccess = true))
	UTargetSystemComponent* TargetSystem;


private:

	virtual void InitAbilityActorInfo() override;

public:

	UMotionWarpingComponent* GetMotionWarping() { return MotionWarping; }

	bool GetTartgetLock();
	void TargetLockOn();
	void TargetLockOff();

};
