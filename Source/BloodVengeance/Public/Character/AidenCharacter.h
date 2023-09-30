#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "AidenCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class AItem;
class UMotionWarpingComponent;

UCLASS()
class BLOODVENGEANCE_API AAidenCharacter : public ACharacterBase
{
	GENERATED_BODY()
	
public:

	AAidenCharacter();

	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;

	virtual void BeginPlay() override;

private:

	// -- ī�޶� --
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent> FollowCamera;
	// -- ī�޶� --
	
	
	
	// -- ���� ���� --

	UPROPERTY(EditAnywhere)
	TSubclassOf<AItem> KatanaClass;

	// -- ���� ���� --
	
	// -- ��� ���� --
	UMotionWarpingComponent* MotionWarping;
	// -- ��� ����--

private:

	// -- �����Ƽ �ý��� --
	void InitAbilityActorInfo();
	// -- �����Ƽ �ý��� --

public:

	// -- ��� ���� --
	UMotionWarpingComponent* GetMotionWarping() { return MotionWarping; }
	// -- ��� ����--



};
