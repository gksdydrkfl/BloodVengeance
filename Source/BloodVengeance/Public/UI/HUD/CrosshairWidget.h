#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CrosshairWidget.generated.h"

class UBorder;
class UCanvasPanelSlot;

UCLASS()
class BLOODVENGEANCE_API UCrosshairWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = true))
	TObjectPtr<UBorder> TopCrosshair;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = true))
	TObjectPtr<UBorder> DownCrosshair;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = true))
	TObjectPtr<UBorder> LeftCrosshair;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget), meta = (AllowPrivateAccess = true))
	TObjectPtr<UBorder> RightCrosshair;

public:

	void SetCrosshair();

	void SetHiddenCrosshair(const bool& NewValue);

	void SetSizeAndPosition(UCanvasPanelSlot* NewPanelSlot, const FVector2D& NewSize, const FVector2D& NewPosition);

};
