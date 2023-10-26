#include "BVGameplayTags.h"
#include "GameplayTagsManager.h"

FBVGameplayTags FBVGameplayTags::GameplayTags;

void FBVGameplayTags::InitGameplayTags()
{
	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.LMB"),	FString("Left Mouse Button"));

	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.RMB"),FString("Right Mouse Button"));

	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.1"),FString("1 Key"));

	GameplayTags.Montage_NextAttackCheck = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.NextAttackCheck"), FString("Can Next Attack Check"));

	GameplayTags.Montage_EndAttackCheck = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.EndAttackCheck"), FString("End Attack Check"));

	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage"), FString("Damage"));

	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effects.HitReact"), FString("HitReact"));

	GameplayTags.Effects_Death = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effects.Death"), FString("Death"));

	
}