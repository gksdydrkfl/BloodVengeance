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

	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;

private:

	//ī�޶�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent> FollowCamera;
	//ī�޶�

private:

	void InitAbilityActorInfo();
};
