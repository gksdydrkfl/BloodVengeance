#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"


struct FBVGameplayTags
{

public:

	static const FBVGameplayTags& Get() { return GameplayTags; }
	static void InitGameplayTags();

	//입력
	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;


	//몽타쥬
	FGameplayTag Montage_NextAttackCheck;
	FGameplayTag Montage_EndAttackCheck;


	//데미지
	FGameplayTag Damage;


	//히트 리액트
	FGameplayTag Effects_HitReact;
	FGameplayTag Effects_Death;

	FGameplayTag Abilities_KatanaBaseAttack;
	FGameplayTag Abilities_BowBaseAttack;

protected:

private:

	static FBVGameplayTags GameplayTags;
};
