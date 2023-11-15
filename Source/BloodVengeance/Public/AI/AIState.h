#pragma once

UENUM(BlueprintType)
enum class EAIState : uint8
{
	AIS_Passive			UMETA(DisplayName = "Passive"),
	AIS_Attacking		UMETA(DisplayName = "Attacking"),
	AIS_Investigating	UMETA(DisplayName = "Inverstigating"),
	AIS_Frozen			UMETA(DisplayName = "Frozen"),
	AIS_Dead			UMETA(DisplayName = "Dead")
};

UENUM(BlueprintType)
enum class EAIMovementState : uint8
{
	AIMS_Idle		UMETA(DisplayName = "Idle"),
	AIMS_Walking	UMETA(DisplayName = "Walking"),
	AIMS_Jogging	UMETA(DisplayName = "Jogging"),
	AIMS_Sprinting	UMETA(DisplayName = "Sprinting")
};

UENUM(BlueprintType)
enum class EAISense : uint8
{
	AIS_None			UMETA(DisplayName = "None"),
	AIS_Sight			UMETA(DisplayName = "Sight"),
	AIS_Hearing			UMETA(DisplayName = "Hearing"),
	AIS_Damage			UMETA(DisplayName = "Damage"),
};