#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AidenAnimInstance.generated.h"

class AAidenCharacter;

UCLASS()
class BLOODVENGEANCE_API UAidenAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	UAidenAnimInstance();

protected:

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:

	AAidenCharacter* Aiden;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = true))
	float Speed = 0.f;

};
