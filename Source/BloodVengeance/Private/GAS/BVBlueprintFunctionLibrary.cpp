#include "GAS/BVBlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Game/BVGameModeBase.h"
#include "AbilitySystemComponent.h"

void UBVBlueprintFunctionLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, const float& Level, UAbilitySystemComponent* ASC)
{
	ABVGameModeBase* BVGameModeBase = Cast<ABVGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));

	if (BVGameModeBase == nullptr)
	{
		return;
	}

	AActor* AvatarActor = ASC->GetAvatarActor();

	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);

	FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

	FGameplayEffectContextHandle PrimaryAttributesContextHandle = ASC->MakeEffectContext();
	PrimaryAttributesContextHandle.AddSourceObject(AvatarActor);

	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes, Level, PrimaryAttributesContextHandle);

	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());
}

void UBVBlueprintFunctionLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC)
{
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);

	for (const TSubclassOf<UGameplayAbility> AbilityClass : CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		ASC->GiveAbility(AbilitySpec);
	}
}

UCharacterClassInfo* UBVBlueprintFunctionLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	const ABVGameModeBase* BVGameMode = Cast<ABVGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (BVGameMode == nullptr)
	{
		return nullptr;
	}
	return BVGameMode->GetCharacterClassInfo();
}