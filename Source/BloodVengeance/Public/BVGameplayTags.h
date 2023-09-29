#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"


struct FBVGameplayTags
{

public:

	static const FBVGameplayTags& Get() { return GameplayTags; }
	static void InitGameplayTags();

	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;

	FGameplayTag Montage_NextAttackCheck;
	FGameplayTag Montage_EndAttackCheck;

protected:

private:

	static FBVGameplayTags GameplayTags;
};