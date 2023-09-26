#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"


struct FBVGameplayTags
{

public:

	static const FBVGameplayTags& Get() { return GameplayTags; }
	void InitGameplayTags();

	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
protected:

private:

	static FBVGameplayTags GameplayTags;
};