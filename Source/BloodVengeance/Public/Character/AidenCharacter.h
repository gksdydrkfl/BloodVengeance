#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "AidenCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class AItem;
class UMotionWarpingComponent;

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

	// -- 카메라 --
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent> FollowCamera;
	// -- 카메라 --
	
	
	
	// -- 무기 관련 --

	UPROPERTY(EditAnywhere)
	TSubclassOf<AItem> KatanaClass;

	// -- 무기 관련 --
	
	// -- 모션 워핑 --
	UMotionWarpingComponent* MotionWarping;
	// -- 모션 워핑--

private:

	// -- 어빌리티 시스템 --
	void InitAbilityActorInfo();
	// -- 어빌리티 시스템 --

public:

	// -- 모션 워핑 --
	UMotionWarpingComponent* GetMotionWarping() { return MotionWarping; }
	// -- 모션 워핑--



};
