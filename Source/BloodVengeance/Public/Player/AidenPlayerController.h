#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Input/InputDataAsset.h"
#include "AidenPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class ABVMainHUD;

UCLASS()
class BLOODVENGEANCE_API AAidenPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	AAidenPlayerController();

protected:

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn* InPawn) override;
private:

	// �Է°���
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMapping;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputDataAsset> InputDataAsset;
	// �Է°���

	ABVMainHUD* BVMainHUD;

public:

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	void CreateHUDWidget();

	ABVMainHUD* GetMainHUD() const { return BVMainHUD; }

protected:



	virtual void OnRep_PlayerState() override;
};
