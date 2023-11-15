#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "Components/TimeLineComponent.h"
#include "AidenCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UMotionWarpingComponent;
class UTargetSystemComponent;
class UGroomComponent;
class AWeapon;
class AAidenPlayerController;

UCLASS()
class BLOODVENGEANCE_API AAidenCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:

	AAidenCharacter();

	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:

	AAidenPlayerController* AidenPlayerController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = true))
	TObjectPtr<USkeletalMeshComponent> Face;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = true))
	TObjectPtr<USkeletalMeshComponent> Legs;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = true))
	TObjectPtr<USkeletalMeshComponent> Torso;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = true))
	TObjectPtr<USkeletalMeshComponent> Feet;



	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent> FollowCamera;

	TObjectPtr<UMotionWarpingComponent> MotionWarping;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TargetSystem", meta = (AllowPrivateAccess = true))
	TObjectPtr<UTargetSystemComponent> TargetSystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Groom", meta = (AllowPrivateAccess = true))
	TObjectPtr<UGroomComponent> Eyebrows;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Groom", meta = (AllowPrivateAccess = true))
	TObjectPtr<UGroomComponent> Hair;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Groom", meta = (AllowPrivateAccess = true))
	TObjectPtr<UGroomComponent> Mustache;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Groom", meta = (AllowPrivateAccess = true))
	TObjectPtr<UGroomComponent> Beard;

	//TEST
	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeapon> BowClass;
	//TEST

	UPROPERTY(EditAnywhere, Category = "ADS", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCurveFloat> ADSFloatCurve;

	UPROPERTY(EditAnywhere, Category = "ADS", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCurveVector> ADSFVectorCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ADS", meta = (AllowPrivateAccess = "true"))
	float ADSTimelineLength;

	FOnTimelineFloat ADSCallbackFloatUpdate;
	FOnTimelineVector ADSCallbackVectorUpdate;

	FOnTimelineEvent ADSCallbackFinish;

	FTimeline ADSTimeline;



private:

	virtual void InitAbilityActorInfo() override;

public:

	AAidenPlayerController* GetAidenPlayerController() const { return AidenPlayerController; }

	UMotionWarpingComponent* GetMotionWarping() const { return MotionWarping; }

	bool GetTartgetLock() const;
	void TargetLockOn();
	void TargetLockOff();
	
	UFUNCTION(BlueprintCallable)
	void EnableMasterPose(USkeletalMeshComponent* SkeletalMeshComponent);

	void SetCameraMode(const float& NewFieldOfView, const FVector NewLocation);

	void SetCallbackADS();

	UFUNCTION()
	void ADSUpdate(float NewValue);
	UFUNCTION()
	void ADSFinish();

};
