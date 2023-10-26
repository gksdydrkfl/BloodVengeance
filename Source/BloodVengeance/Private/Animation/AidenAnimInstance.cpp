#include "Animation/AidenAnimInstance.h"
#include "Character/AidenCharacter.h"
#include "BloodVengeance/DebugMacro.h"
#include "KismetAnimationLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

UAidenAnimInstance::UAidenAnimInstance()
{
	bTargetLock = false;

	bHasVelocity = false;

	DisplacementSinceLastUpdate = 0.f;

	WorldLocation = FVector::ZeroVector;

	bIsFirstUpdate = true;

	WorldRotation = FRotator::ZeroRotator;

	YawDeltaSinceLastUpdate = 0.f;

	YawDeltaSpeed = 0.f;

	AdditiveLeanAngle = 0.f;

	LocalVelocity2D = FVector::ZeroVector;

	LocalVelocityDirectionAgle = 0.f;

	LocalVelocityDirectionAngleWithOffset = 0.f;

	LocalVelocityDirection = EAnimEnumCardinalDirection::AECD_Forward;

	LocalVelocityDirectionNoOffset = EAnimEnumCardinalDirection::AECD_Forward;

	CardinalDirectionDeadZone = 10.f;

	LocalAcceleration2D = FVector::ZeroVector;

	bHasAcceleration = false;

	PivotDirection2D = FVector::ZeroVector;

	CardinalDirectionFromAcceleration = EAnimEnumCardinalDirection::AECD_Forward;

	bIsRunningIntoWall = false;

	bIsOnGround = false;

	bCrouchStateChange = false;

	bIsCrouching = false;

	bGameplayTagIsADS = false;

	bWasADSLastUpdate = false;

	bADSStateChanged = false;

	bGameplayTagIsAttack = false;

	TimeSinceAttackWeapon = 9999.f;

	bIsJumping = false;

	bIsFalling = false;

	UpperBodyDynamicAddtiveWeight = 0.f;

	RootYawOffsetMode = ERootYawOffsetMode::RYOM_BlendOut;

	bEnableRootYawOffset = true;

	RootYawOffsetAngleClamp = FVector2D(-120.f, 100.f);

	RootYawOffsetAngleClampCrouched = FVector2D(-90.f, 80.f);

	RootYawOffset = 0.f;

	AimYaw = 0.f;

	bGameplayTagIsDashing = true;

	RootYawOffsetSpringState = FFloatSpringState();

	AimPitch = 0.f;

	TimeToJumpApex = 0.f;

	StartDirection = EAnimEnumCardinalDirection::AECD_Forward;

	bLinkedLayerChanged = false;

	LastLinkedLayer = nullptr;

	LastPivotTime = 0.f;

	PivotInitialDirection = EAnimEnumCardinalDirection::AECD_Forward;
}

void UAidenAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Aiden = Cast<AAidenCharacter>(TryGetPawnOwner());
}

void UAidenAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Aiden == nullptr)
	{
		Aiden = Cast<AAidenCharacter>(TryGetPawnOwner());
	}
	if (Aiden == nullptr)
	{
		return;
	}

	FVector Velocity = Aiden->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Size();

	Direction = UKismetAnimationLibrary::CalculateDirection(Velocity, Aiden->GetActorRotation());

	bTargetLock = GetTargetLock();

	UpdateLocationData(DeltaSeconds);

	UpdateRotationData();

	UpdateVelocityData();

	UpdateAccelerationData();

	UpdateWallDetectionHeuristic();

	UpdateCharacterState(DeltaSeconds);

	UpdateBlendWeightData(DeltaSeconds);

	UpdateRootYawOffset(DeltaSeconds);

	UpdateAimingDate();

	UpdateJumpFallData();

	bIsFirstUpdate = false;
}

bool UAidenAnimInstance::GetTargetLock()
{
	if (Aiden)
	{
		return Aiden->GetTartgetLock();
	}

	return false;
}

EAnimEnumCardinalDirection UAidenAnimInstance::SelectCardinalDirectionFromAngle(const float& Angle, const float& DeadZone, const EAnimEnumCardinalDirection& CurrentDirection, bool bUseCurrentDirection)
{
	const float AbsAngle = FMath::Abs(Angle);
	float FwdDeadZone = DeadZone;
	float BwdDeadZone = DeadZone;

	if (bUseCurrentDirection)
	{
		switch (CurrentDirection)
		{
		case EAnimEnumCardinalDirection::AECD_Forward:
			FwdDeadZone = FwdDeadZone * 2.f;
			break;
		case EAnimEnumCardinalDirection::AECD_Backward:
			BwdDeadZone = BwdDeadZone * 2.f;
			break;
		}
	}

	if (AbsAngle <= (FwdDeadZone + 45.f))
	{
		return EAnimEnumCardinalDirection::AECD_Forward;
	}
	else
	{
		if (AbsAngle >= (135.f - BwdDeadZone))
		{
			return EAnimEnumCardinalDirection::AECD_Backward;
		}
		else
		{
			if (Angle > 0.f)
			{
				return EAnimEnumCardinalDirection::AECD_Right;
			}
			else
			{
				return EAnimEnumCardinalDirection::AECD_Left;
			}
		}
	}
}

EAnimEnumCardinalDirection UAidenAnimInstance::GetOppositeCardinalDirection(EAnimEnumCardinalDirection CurrentDirection)
{
	switch (CurrentDirection)
	{
	case EAnimEnumCardinalDirection::AECD_Forward:
		return EAnimEnumCardinalDirection::AECD_Forward;
	case EAnimEnumCardinalDirection::AECD_Backward:
		return EAnimEnumCardinalDirection::AECD_Backward;
	case EAnimEnumCardinalDirection::AECD_Left:
		return EAnimEnumCardinalDirection::AECD_Left;
	case EAnimEnumCardinalDirection::AECD_Right:
		return EAnimEnumCardinalDirection::AECD_Right;
	}

	return EAnimEnumCardinalDirection();
}

void UAidenAnimInstance::SetRootYawOffset(const float& InRootYawOffset)
{
	if (bEnableRootYawOffset)
	{
		const FVector2D NewVector = bIsCrouching ? RootYawOffsetAngleClampCrouched : RootYawOffsetAngleClamp;

		float InRootYawOffsetNormal = UKismetMathLibrary::NormalizeAxis(InRootYawOffset);

		float InRootYawOffsetValue = UKismetMathLibrary::ClampAngle(InRootYawOffsetNormal, NewVector.X, NewVector.Y);

		bool bIsEqual = UKismetMathLibrary::EqualEqual_DoubleDouble(NewVector.X, NewVector.Y);

		RootYawOffset = UKismetMathLibrary::SelectFloat(InRootYawOffsetNormal, InRootYawOffsetValue, bIsEqual);

		AimYaw = RootYawOffset * -1.f;
	}
	else
	{
		RootYawOffset = 0.f;
		AimYaw = 0.f;
	}
}

void UAidenAnimInstance::SetupStartState()
{
	StartDirection = LocalVelocityDirection;
}

void UAidenAnimInstance::UpdateLocationData(const float& DeltaTime)
{
	DisplacementSinceLastUpdate = UKismetMathLibrary::VSizeXY(Aiden->GetActorLocation() - WorldLocation);

	WorldLocation = Aiden->GetActorLocation();

	DisPlacementSpeed = UKismetMathLibrary::SafeDivide(DisplacementSinceLastUpdate, DeltaTime);

	if(bIsFirstUpdate)
	{
		DisplacementSinceLastUpdate = 0.f;

		DisPlacementSpeed = 0.f;
	}
}

void UAidenAnimInstance::UpdateRotationData()
{
	const FRotator Rotation = Aiden->GetActorRotation();

	YawDeltaSinceLastUpdate = Rotation.Yaw - WorldRotation.Yaw;

	YawDeltaSpeed = UKismetMathLibrary::SafeDivide(YawDeltaSinceLastUpdate, GetDeltaSeconds());

	WorldRotation = Aiden->GetActorRotation();

	bool bPick = false;

	if (bIsCrouching || bGameplayTagIsADS)
	{
		bPick = true;
	}

	AdditiveLeanAngle = YawDeltaSpeed * UKismetMathLibrary::SelectFloat(0.025f, 0.0375f, bPick);

	if (bIsFirstUpdate)
	{
		YawDeltaSinceLastUpdate = 0.f;

		AdditiveLeanAngle = 0.f;
	}
}

void UAidenAnimInstance::UpdateVelocityData()
{
	const bool bWasMovingLastUpdate = !UKismetMathLibrary::Vector_IsZero(LocalVelocity2D);

	WorldVelocity = Aiden->GetVelocity();

	const FVector WorldVelocity2D = FVector(WorldVelocity.X, WorldVelocity.Y, 0.f);

	LocalVelocity2D = UKismetMathLibrary::LessLess_VectorRotator(WorldVelocity2D, WorldRotation);

	LocalVelocityDirectionAgle = UKismetAnimationLibrary::CalculateDirection(WorldVelocity2D, WorldRotation);

	//RootYawOffset = 10.f;

	LocalVelocityDirectionAngleWithOffset = LocalVelocityDirectionAgle - RootYawOffset;

	LocalVelocityDirection = SelectCardinalDirectionFromAngle(LocalVelocityDirectionAngleWithOffset, CardinalDirectionDeadZone, LocalVelocityDirection, bWasMovingLastUpdate);

	LocalVelocityDirectionNoOffset = SelectCardinalDirectionFromAngle(LocalVelocityDirectionAgle, CardinalDirectionDeadZone, LocalVelocityDirectionNoOffset, bWasMovingLastUpdate);

	bHasVelocity = !UKismetMathLibrary::NearlyEqual_FloatFloat(UKismetMathLibrary::VSizeXYSquared(LocalVelocity2D), 0.f, 0.000001f);
}

void UAidenAnimInstance::UpdateAccelerationData()
{
	FVector Acceleration = Aiden->GetCharacterMovement()->GetCurrentAcceleration();

	const FVector WorldAcceleration2D = FVector(Acceleration.X, Acceleration.Y, 0.f);

	LocalAcceleration2D = UKismetMathLibrary::LessLess_VectorRotator(WorldAcceleration2D, WorldRotation);

	bHasAcceleration = !UKismetMathLibrary::NearlyEqual_FloatFloat(UKismetMathLibrary::VSizeXYSquared(LocalAcceleration2D), 0.f, 0.000001f);

	const FVector WorldAcceleration2DNormal = UKismetMathLibrary::Normal(WorldAcceleration2D, 0.0001f);

	const FVector WorldAccelerationLerp = UKismetMathLibrary::VLerp(PivotDirection2D, WorldAcceleration2DNormal, 0.5f);

	PivotDirection2D = UKismetMathLibrary::Normal(WorldAccelerationLerp, 0.0001f);

	const float DirectionAngle = UKismetAnimationLibrary::CalculateDirection(PivotDirection2D, WorldRotation);

	const EAnimEnumCardinalDirection CurrentDirection = SelectCardinalDirectionFromAngle(DirectionAngle, CardinalDirectionDeadZone, EAnimEnumCardinalDirection::AECD_Forward, false);

	CardinalDirectionFromAcceleration = GetOppositeCardinalDirection(CurrentDirection);
}

void UAidenAnimInstance::UpdateWallDetectionHeuristic()
{
	if ((UKismetMathLibrary::VSizeXY(LocalAcceleration2D) > 0.1f) &&
		(UKismetMathLibrary::VSizeXY(LocalVelocity2D) < 200.f) &&
		UKismetMathLibrary::InRange_FloatFloat(UKismetMathLibrary::Dot_VectorVector(UKismetMathLibrary::Normal(LocalAcceleration2D, 0.0001f), UKismetMathLibrary::Normal(LocalVelocity2D, 0.0001f)), -0.6f, 0.6f, true, true)
		)
	{
		bIsRunningIntoWall = true;
	}
	else
	{
		bIsRunningIntoWall = false;
	}

}

void UAidenAnimInstance::UpdateCharacterState(const float& DeltaTime)
{
	bIsOnGround = Aiden->GetMovementComponent()->IsMovingOnGround();

	bool bWasCrouchingLastUpdate = bIsCrouching;

	bIsCrouching = Aiden->GetMovementComponent()->IsCrouching();

	bCrouchStateChange = bIsCrouching != bWasCrouchingLastUpdate ? true : false;

	bADSStateChanged = bGameplayTagIsADS != bWasADSLastUpdate ? true : false;

	bWasADSLastUpdate = bGameplayTagIsADS;

	if (bGameplayTagIsAttack)
	{
		TimeSinceAttackWeapon = 0.f;
	}
	else
	{
		TimeSinceAttackWeapon = TimeSinceAttackWeapon + DeltaTime;
	}

	bIsJumping = false;
	bIsFalling = false;

	if (Aiden->GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Falling)
	{
		if (WorldVelocity.Z > 0.f)
		{
			bIsJumping = true;
		}
		else
		{
			bIsFalling = true;
		}
	}
}

void UAidenAnimInstance::UpdateBlendWeightData(const float& DeltaTime)
{
	bool bSelect = IsAnyMontagePlaying() && bIsOnGround ? true : false;

	UpperBodyDynamicAddtiveWeight = UKismetMathLibrary::SelectFloat(1.f, UKismetMathLibrary::FInterpTo(UpperBodyDynamicAddtiveWeight, 0.f, DeltaTime, 6.f), bSelect);
}

void UAidenAnimInstance::UpdateRootYawOffset(const float& DeltaTime)
{
	if (RootYawOffsetMode == ERootYawOffsetMode::RYOM_Accumulate)
	{
		SetRootYawOffset(RootYawOffset - YawDeltaSinceLastUpdate);
	}
	if (RootYawOffsetMode == ERootYawOffsetMode::RYOM_BlendOut || bGameplayTagIsDashing)
	{
		SetRootYawOffset(UKismetMathLibrary::FloatSpringInterp(RootYawOffset, 0.f, RootYawOffsetSpringState, 80.f, 1.f, DeltaTime, 1.f, 0.5f));
	}

	RootYawOffsetMode = ERootYawOffsetMode::RYOM_BlendOut;
}

void UAidenAnimInstance::UpdateAimingDate()
{
	AimPitch = UKismetMathLibrary::NormalizeAxis(Aiden->GetBaseAimRotation().Pitch);
}

void UAidenAnimInstance::UpdateJumpFallData()
{
	if (bIsJumping)
	{
		float WorldZ = 0.f - WorldVelocity.Z;
		TimeToJumpApex = WorldZ / Aiden->GetMovementComponent()->GetGravityZ();
	}
	else
	{
		TimeToJumpApex = 0.f;
	}
}

bool UAidenAnimInstance::GetMovingPerpendicularToInitialPivot()
{
	return ((PivotInitialDirection == EAnimEnumCardinalDirection::AECD_Forward || PivotInitialDirection == EAnimEnumCardinalDirection::AECD_Backward) &&
		(!(LocalVelocityDirection == EAnimEnumCardinalDirection::AECD_Forward || LocalVelocityDirection == EAnimEnumCardinalDirection::AECD_Backward)) ||
		(PivotInitialDirection == EAnimEnumCardinalDirection::AECD_Left || PivotInitialDirection == EAnimEnumCardinalDirection::AECD_Right) &&
		!(LocalVelocityDirection == EAnimEnumCardinalDirection::AECD_Left || LocalVelocityDirection == EAnimEnumCardinalDirection::AECD_Right)
		);
}


