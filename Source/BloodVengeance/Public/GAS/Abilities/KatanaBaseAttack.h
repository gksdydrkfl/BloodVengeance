#pragma once

#include "CoreMinimal.h"
#include "GAS/BVGameplayAbility.h"
#include "KatanaBaseAttack.generated.h"

class AKatana;

UCLASS()
class BLOODVENGEANCE_API UKatanaBaseAttack : public UBVGameplayAbility
{
	GENERATED_BODY()
	
public:

	UKatanaBaseAttack();

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack Properties", meta = (AllowPrivateAccess = true))
	int32 CurrentCombo;

	//FVector LastLocation;

protected:

public:

	UFUNCTION(BlueprintCallable)
	void BaseAttack();

	UFUNCTION(BlueprintCallable)
	void ResetCombo();

	UFUNCTION(BlueprintCallable)
	void UpdateMotionWarping();

private:

	AKatana* GetKatana();
};
