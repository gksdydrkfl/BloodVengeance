#pragma once

#include "CoreMinimal.h"

#define DRAW_SPHERE(Location) if (GetWorld()) DrawDebugSphere(GetWorld(), Location, 25.f, 12, FColor::Red, true);
#define DRAW_SPHERE_COLOR(Location, Color) DrawDebugSphere(GetWorld(), Location, 8.f, 12, Color, false, 5.f);
#define DRAW_SPHERE_SingleFrame(Location) if (GetWorld()) DrawDebugSphere(GetWorld(), Location, 25.f, 12, FColor::Red, false, -1.f);
#define DRAW_LINE(StartLocation, EndLocation) if (GetWorld()) DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, true, -1.f, 0, 1.f);
#define DRAW_LINE_SingleFrame(StartLocation, EndLocation) if (GetWorld()) DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, -1.f, 0, 1.f);
#define DRAW_POINT(Location) if (GetWorld()) DrawDebugPoint(GetWorld(), Location, 15.f, FColor::Red, true);
#define DRAW_POINT_SingleFrame(Location) if (GetWorld()) DrawDebugPoint(GetWorld(), Location, 15.f, FColor::Red, false, -1.f);
#define DRAW_VECTOR(StartLocation, EndLocation) if (GetWorld()) \
	{ \
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, true, -1.f, 0, 1.f); \
		DrawDebugPoint(GetWorld(), EndLocation, 15.f, FColor::Red, true); \
	}
#define DRAW_VECTOR_SingleFrame(StartLocation, EndLocation) if (GetWorld()) \
	{ \
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, -1.f, 0, 1.f); \
		DrawDebugPoint(GetWorld(), EndLocation, 15.f, FColor::Red, false, -1.f); \
	}


class BLOODVENGEANCE_API Debug
{
public:
	static void Log(int32 InValue, int32 InKey = -1, float InDuration = 5, FColor InColor = FColor::Blue)
	{
		GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, FString::FromInt(InValue));
	}
	static void Log(float InValue, int32 InKey = -1, float InDuration = 5, FColor InColor = FColor::Blue)
	{
		GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, FString::SanitizeFloat(InValue));
	}
	static void Log(double InValue, int32 InKey = -1, float InDuration = 5, FColor InColor = FColor::Blue)
	{
		GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, FString::SanitizeFloat(InValue));
	}
	static void Log(const FString& InValue, int32 InKey = -1, float InDuration = 5, FColor InColor = FColor::Blue)
	{
		GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, InValue);
		UE_LOG(LogTemp, Log, TEXT("%s"), *InValue);
	}
	static void Log(const FVector& InValue, int32 InKey = -1, float InDuration = 5, FColor InColor = FColor::Blue)
	{
		GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, InValue.ToString());
	}
	static void Log(const FRotator& InValue, int32 InKey = -1, float InDuration = 5, FColor InColor = FColor::Blue)
	{
		GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, InValue.ToString());
	}
	static void Log(const UObject* InValue, int32 InKey = -1, float InDuration = 5, FColor InColor = FColor::Blue)
	{
		FString str;

		if (!InValue) return;

		if (!!InValue)
			str.Append(InValue->GetName());

		str.Append(!!InValue ? " Not Null" : "Null");

		GEngine->AddOnScreenDebugMessage(InKey, InDuration, InColor, str);
	}
	static void Print(const FString& InFileName, const FString& InFuncName, int32 InLineNumber)
	{
		int32 index = 0, length = 0;
		InFileName.FindLastChar(L'\\', index);

		length = InFileName.Len() - 1;
		FString fileName = InFileName.Right(length - index);


		FString str;
		str.Append(fileName);
		str.Append(", ");
		str.Append(InFuncName);
		str.Append(", ");
		str.Append(FString::FromInt(InLineNumber));

		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, str);
	}
};
