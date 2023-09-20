#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AidenPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class BLOODVENGEANCE_API AAidenPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	AAidenPlayerController();

protected:

	virtual void BeginPlay();

	virtual void SetupInputComponent();

private:

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMapping;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

public:

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
};
