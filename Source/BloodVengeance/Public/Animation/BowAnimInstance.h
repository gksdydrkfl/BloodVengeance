#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BowAnimInstance.generated.h"

class ACharacterBase;
class ABow;

UCLASS()
class BLOODVENGEANCE_API UBowAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	UBowAnimInstance();

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = true))
	TObjectPtr<ACharacterBase> CharacterBase;

	TObjectPtr<ABow> Bow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bow Properties", meta = (AllowPrivateAccess = true))
	FTransform RightHandTransform;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bow Properties", meta = (AllowPrivateAccess = true))
	bool bString;

public:

	void SetCharacterBase(ACharacterBase* NewCharacter);

};
