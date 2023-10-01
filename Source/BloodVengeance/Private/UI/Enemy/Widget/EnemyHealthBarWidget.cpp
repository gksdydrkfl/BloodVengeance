#include "UI/Enemy/Widget/EnemyHealthBarWidget.h"
#include "Components/ProgressBar.h"

void UEnemyHealthBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//HealthBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HealthBar")));
}

void UEnemyHealthBarWidget::UpdateHealthBar(const float& NewValue)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(NewValue);
	}
}
