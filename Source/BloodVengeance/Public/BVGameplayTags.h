#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"


struct FBVGameplayTags
{

public:

	static const FBVGameplayTags& Get() { return GameplayTags; }
	static void InitGameplayTags();

	//�Է�
	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;


	//��Ÿ��
	FGameplayTag Montage_NextAttackCheck;
	FGameplayTag Montage_EndAttackCheck;


	//������
	FGameplayTag Damage;


	//��Ʈ ����Ʈ
	FGameplayTag Effects_HitReact;
	FGameplayTag Effects_Death;

	FGameplayTag Abilities_KatanaBaseAttack;
	FGameplayTag Abilities_BowBaseAttack;

protected:

private:

	static FBVGameplayTags GameplayTags;
};
