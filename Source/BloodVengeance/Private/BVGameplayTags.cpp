#include "BVGameplayTags.h"
#include "GameplayTagsManager.h"

FBVGameplayTags FBVGameplayTags::GameplayTags;

void FBVGameplayTags::InitGameplayTags()
{
	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.LMB"),	FString("Left Mouse Button"));

	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.RMB"),FString("Right Mouse Button"));

	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.1"),FString("1 Key"));
}