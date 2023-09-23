#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

class UProgressBar;

UCLASS()
class BLOODVENGEANCE_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;

public:

	void UpdateHealthBar(const float& NewValue);

};
