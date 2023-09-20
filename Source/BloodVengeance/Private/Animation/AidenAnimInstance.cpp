#include "Animation/AidenAnimInstance.h"
#include "Character/AidenCharacter.h"
#include "BloodVengeance/DebugMacro.h"
UAidenAnimInstance::UAidenAnimInstance()
{

}

void UAidenAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Aiden = Cast<AAidenCharacter>(TryGetPawnOwner());
}

void UAidenAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Aiden == nullptr)
	{
		Aiden = Cast<AAidenCharacter>(TryGetPawnOwner());
	}
	if (Aiden == nullptr)
	{
		return;
	}

	FVector Velocity = Aiden->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Size();
}
