#include "UI/Enemy/Widget/EnemyHealthBarWidget.h"
#include "Components/ProgressBar.h"

void UEnemyHealthBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UEnemyHealthBarWidget::UpdateHealthBar(const float& NewValue)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(NewValue);
	}
}
