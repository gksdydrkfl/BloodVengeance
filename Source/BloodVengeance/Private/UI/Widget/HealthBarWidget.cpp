#include "UI/Widget/HealthBarWidget.h"
#include "Components/ProgressBar.h"

void UHealthBarWidget::UpdateHealthBar(const float& NewValue)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(NewValue);
	}
}
