#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Data/CharacterClassInfo.h"
#include "BVBlueprintFunctionLibrary.generated.h"

class UAbilitySystemComponent;

UCLASS()
class BLOODVENGEANCE_API UBVBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	static UCharacterClassInfo* GetCharacterClassInfo(const UObject* WorldContextObject);

	static void InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, const float& Level, UAbilitySystemComponent* ASC);

	static void GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, ECharacterClass& CharacterClass);

};
