#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "AidenCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class BLOODVENGEANCE_API AAidenCharacter : public ACharacterBase
{
	GENERATED_BODY()
	
public:

	AAidenCharacter();

private:

	//카메라
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent> FollowCamera;
	//카메라

};
