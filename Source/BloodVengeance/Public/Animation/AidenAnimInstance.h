#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "AidenAnimInstance.generated.h"

class AAidenCharacter;

UENUM(BlueprintType)
enum class ERootYawOffsetMode : uint8
{
	RYOM_BlendOut	UMETA(DisplayName = "BlendOut"),
	RYOM_Hold		UMETA(DisplayName = "Hold"),
	RYOM_Accumulate	UMETA(DisplayName = "Accumulate")
};

UENUM(BlueprintType)
enum class EAnimEnumCardinalDirection : uint8
{
	AECD_Forward	UMETA(DisplayName = "Forward"),
	AECD_Backward	UMETA(DisplayName = "Backward"),
	AECD_Left		UMETA(DisplayName = "Left"),
	AECD_Right		UMETA(DisplayName = "Right")
};

UCLASS()
class BLOODVENGEANCE_API UAidenAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	UAidenAnimInstance();

protected:

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:

	AAidenCharacter* Aiden;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = true))
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = true))
	float Direction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TargetSystem", meta = (AllowPrivateAccess = true))
	bool bTargetLock;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Locomotion Properties", meta = (AllowPrivateAccess = true))
	bool bHasVelocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Location Data", meta = (AllowPrivateAccess = true))
	float DisplacementSinceLastUpdate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Location Data", meta = (AllowPrivateAccess = true))
	float DisPlacementSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Location Data", meta = (AllowPrivateAccess = true))
	FVector WorldLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Velocity Data", meta = (AllowPrivateAccess = true))
	FVector WorldVelocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setting", meta = (AllowPrivateAccess = true))
	bool bIsFirstUpdate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rotation Data", meta = (AllowPrivateAccess = true))
	FRotator WorldRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rotation Data", meta = (AllowPrivateAccess = true))
	float YawDeltaSinceLastUpdate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rotation Data", meta = (AllowPrivateAccess = true))
	float YawDeltaSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rotation Data", meta = (AllowPrivateAccess = true))
	float AdditiveLeanAngle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Velocity Data", meta = (AllowPrivateAccess = true))
	FVector LocalVelocity2D;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Velocity Data", meta = (AllowPrivateAccess = true))
	float LocalVelocityDirectionAgle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Velocity Data", meta = (AllowPrivateAccess = true))
	float LocalVelocityDirectionAngleWithOffset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Velocity Data", meta = (AllowPrivateAccess = true))
	EAnimEnumCardinalDirection LocalVelocityDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Velocity Data", meta = (AllowPrivateAccess = true))
	EAnimEnumCardinalDirection LocalVelocityDirectionNoOffset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Velocity Data", meta = (AllowPrivateAccess = true))
	float CardinalDirectionDeadZone;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Acceleration Data", meta = (AllowPrivateAccess = true))
	FVector LocalAcceleration2D;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Acceleration Data", meta = (AllowPrivateAccess = true))
	bool bHasAcceleration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Acceleration Data", meta = (AllowPrivateAccess = true))
	FVector PivotDirection2D;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LocomotionSM Data", meta = (AllowPrivateAccess = true))
	EAnimEnumCardinalDirection CardinalDirectionFromAcceleration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character State Data", meta = (AllowPrivateAccess = true))
	bool bIsRunningIntoWall;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character State Data", meta = (AllowPrivateAccess = true))
	bool bIsOnGround;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character State Data", meta = (AllowPrivateAccess = true))
	bool bCrouchStateChange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character State Data", meta = (AllowPrivateAccess = true))
	bool bIsCrouching;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay Tag Bindings", meta = (AllowPrivateAccess = true))
	bool bGameplayTagIsADS;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character State Data", meta = (AllowPrivateAccess = true))
	bool bWasADSLastUpdate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character State Data", meta = (AllowPrivateAccess = true))
	bool bADSStateChanged;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay Tag Bindings", meta = (AllowPrivateAccess = true))
	bool bGameplayTagIsAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character State Data", meta = (AllowPrivateAccess = true))
	float TimeSinceAttackWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character State Data", meta = (AllowPrivateAccess = true))
	bool bIsJumping;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character State Data", meta = (AllowPrivateAccess = true))
	bool bIsFalling;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character State Data", meta = (AllowPrivateAccess = true))
	float UpperBodyDynamicAddtiveWeight;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Turn In Place", meta = (AllowPrivateAccess = true))
	ERootYawOffsetMode RootYawOffsetMode;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setting", meta = (AllowPrivateAccess = true))
	bool bEnableRootYawOffset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turn In Place", meta = (AllowPrivateAccess = true))
	FVector2D RootYawOffsetAngleClamp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turn In Place", meta = (AllowPrivateAccess = true))
	FVector2D RootYawOffsetAngleClampCrouched;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turn In Place", meta = (AllowPrivateAccess = true))
	float RootYawOffset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turn In Place", meta = (AllowPrivateAccess = true))
	float AimYaw;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay Tag Bindings", meta = (AllowPrivateAccess = true))
	bool bGameplayTagIsDashing;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turn In Place", meta = (AllowPrivateAccess = true))
	FFloatSpringState RootYawOffsetSpringState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Aiming Data", meta = (AllowPrivateAccess = true))
	float AimPitch;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character State Data", meta = (AllowPrivateAccess = true))
	float TimeToJumpApex;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LocomotionSM Data", meta = (AllowPrivateAccess = true))
	EAnimEnumCardinalDirection StartDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Linked Layer Data", meta = (AllowPrivateAccess = true))
	bool bLinkedLayerChanged;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Linked Layer Data", meta = (AllowPrivateAccess = true))
	TObjectPtr<UAnimInstance> LastLinkedLayer;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LocomotionSM Data", meta = (AllowPrivateAccess = true))
	float LastPivotTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LocomotionSM Data", meta = (AllowPrivateAccess = true))
	EAnimEnumCardinalDirection PivotInitialDirection;
public:

	UFUNCTION(BlueprintCallable)
	bool GetTargetLock();

	EAnimEnumCardinalDirection SelectCardinalDirectionFromAngle(const float& Angle, const float& DeadZone, const EAnimEnumCardinalDirection& CurrentDirection, bool bUseCurrentDirection);
	EAnimEnumCardinalDirection GetOppositeCardinalDirection(EAnimEnumCardinalDirection CurrentDirection);
	void SetRootYawOffset(const float& InRootYawOffset);

	void SetupStartState();

	void UpdateLocationData(const float& DeltaTime);
	void UpdateRotationData();
	void UpdateVelocityData();
	void UpdateAccelerationData();
	void UpdateWallDetectionHeuristic();
	void UpdateCharacterState(const float& Deltatime);
	void UpdateBlendWeightData(const float& DeltaTime);
	void UpdateRootYawOffset(const float& DeltaTime);
	void UpdateAimingDate();
	void UpdateJumpFallData();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetMovingPerpendicularToInitialPivot();
};


