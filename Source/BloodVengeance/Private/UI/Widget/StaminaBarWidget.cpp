#include "UI/Widget/StaminaBarWidget.h"
#include "Components/ProgressBar.h"

void UStaminaBarWidget::UpdateStaminaBar(const float& NewValue)
{
	if (StaminaBar)
	{
		StaminaBar->SetPercent(NewValue);
	}
}
