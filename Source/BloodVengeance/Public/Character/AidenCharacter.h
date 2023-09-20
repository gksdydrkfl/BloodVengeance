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

	//ī�޶�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent> FollowCamera;
	//ī�޶�

};
