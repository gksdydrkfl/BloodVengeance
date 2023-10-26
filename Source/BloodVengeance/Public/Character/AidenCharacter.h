#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "AidenCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class AItem;
class UMotionWarpingComponent;
class UTargetSystemComponent;
class UGroomComponent;

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


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = true))
	USkeletalMeshComponent* Face;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = true))
	USkeletalMeshComponent* Legs;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = true))
	USkeletalMeshComponent* Torso;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = true))
	USkeletalMeshComponent* Feet;



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent> FollowCamera;



	UPROPERTY(EditAnywhere)
	TSubclassOf<AItem> KatanaClass;

	UMotionWarpingComponent* MotionWarping;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TargetSystem", meta = (AllowPrivateAccess = true))
	UTargetSystemComponent* TargetSystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Groom", meta = (AllowPrivateAccess = true))
	UGroomComponent* Eyebrows;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Groom", meta = (AllowPrivateAccess = true))
	UGroomComponent* Hair;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Groom", meta = (AllowPrivateAccess = true))
	UGroomComponent* Mustache;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Groom", meta = (AllowPrivateAccess = true))
	UGroomComponent* Beard;

private:

	virtual void InitAbilityActorInfo() override;

public:

	UMotionWarpingComponent* GetMotionWarping() { return MotionWarping; }

	bool GetTartgetLock();
	void TargetLockOn();
	void TargetLockOff();
	
	UFUNCTION(BlueprintCallable)
	void EnableMasterPose(USkeletalMeshComponent* SkeletalMeshComponent);

};
