#include "UI/HUD/CrosshairWidget.h"
#include "Components/Border.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"

#include "BloodVengeance/DebugMacro.h"
void UCrosshairWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetCrosshair();
}

void UCrosshairWidget::SetCrosshair()
{
	if (TopCrosshair == nullptr)
	{
		return;
	}
	if (DownCrosshair == nullptr)
	{
		return;
	}
	if (LeftCrosshair == nullptr)
	{
		return;
	}
	if (RightCrosshair == nullptr)
	{
		return;
	}

	FVector2D ViewportSize;

	GEngine->GameViewport->GetViewportSize(ViewportSize);
	ViewportSize.X = (ViewportSize.X * 0.5f) -16.f;
	ViewportSize.Y = (ViewportSize.Y * 0.5f) -16.f;

	UCanvasPanelSlot* CrosshairSlot = nullptr;

	const float Scale = UWidgetLayoutLibrary::GetViewportScale(this);
	ViewportSize /= Scale;

	CrosshairSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(TopCrosshair);
	SetSizeAndPosition(CrosshairSlot, FVector2D(32.f, 32.f), FVector2D(ViewportSize.X, ViewportSize.Y - 10.f));
	CrosshairSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(DownCrosshair);
	SetSizeAndPosition(CrosshairSlot, FVector2D(32.f, 32.f), FVector2D(ViewportSize.X, ViewportSize.Y + 10.f));
	CrosshairSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(LeftCrosshair);
	SetSizeAndPosition(CrosshairSlot, FVector2D(32.f, 32.f), FVector2D(ViewportSize.X - 10.f, ViewportSize.Y));
	CrosshairSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(RightCrosshair);
	SetSizeAndPosition(CrosshairSlot, FVector2D(32.f, 32.f), FVector2D(ViewportSize.X + 10.f, ViewportSize.Y));

	TopCrosshair->SetVisibility(ESlateVisibility::Hidden);
	DownCrosshair->SetVisibility(ESlateVisibility::Hidden);
	LeftCrosshair->SetVisibility(ESlateVisibility::Hidden);
	RightCrosshair->SetVisibility(ESlateVisibility::Hidden);
}

void UCrosshairWidget::SetHiddenCrosshair(const bool& NewValue)
{
	if (TopCrosshair == nullptr)
	{
		return;
	}
	if (DownCrosshair == nullptr)
	{
		return;
	}
	if (LeftCrosshair == nullptr)
	{
		return;
	}
	if (RightCrosshair == nullptr)
	{
		return;
	}

	ESlateVisibility CrosshairSlateVisibility;
	if (NewValue)
	{
		CrosshairSlateVisibility = ESlateVisibility::Hidden;
	}
	else
	{
		CrosshairSlateVisibility = ESlateVisibility::Visible;
	}

	TopCrosshair->SetVisibility(CrosshairSlateVisibility);
	DownCrosshair->SetVisibility(CrosshairSlateVisibility);
	LeftCrosshair->SetVisibility(CrosshairSlateVisibility);
	RightCrosshair->SetVisibility(CrosshairSlateVisibility);
}

void UCrosshairWidget::SetSizeAndPosition(UCanvasPanelSlot* NewPanelSlot, const FVector2D& NewSize, const FVector2D& NewPosition)
{
	if (NewPanelSlot == nullptr)
	{
		return;
	}

	NewPanelSlot->SetSize(NewSize);
	NewPanelSlot->SetPosition(NewPosition);
}
