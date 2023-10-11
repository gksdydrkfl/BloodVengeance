#include "Character/Enemy/Enemy.h"
#include "GAS/BVAbilitySystemComponent.h"
#include "GAS/BVAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "UI/Enemy/Widget/EnemyHealthBarWidget.h"
#include "BloodVengeance/DebugMacro.h"

AEnemy::AEnemy()
{
	AbilitySystemComponent = CreateDefaultSubobject<UBVAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UBVAttributeSet>("AttributeSet");

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
	HealthBar->SetDrawSize(FVector2D(150.f, 10.f));
	HealthBar->SetRelativeLocation(FVector(0.f, 0.f, 150.f));
	HealthBar->SetWidgetSpace(EWidgetSpace::Screen);
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	InitAbilityActorInfo();

	UBVAttributeSet* Attribute = Cast<UBVAttributeSet>(AttributeSet);
	if (Attribute)
	{
		HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			AttributeSet->GetHealthAttribute()).AddUObject(this, &AEnemy::HealthChanged);
	}
}

void AEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void AEnemy::HealthChanged(const FOnAttributeChangeData& Data)
{
	const float Health = Data.NewValue;

	UEnemyHealthBarWidget* HealthBarWidget = Cast<UEnemyHealthBarWidget>(HealthBar->GetUserWidgetObject());

	if (HealthBarWidget)
	{
		HealthBarWidget->UpdateHealthBar(Health / AttributeSet->GetMaxHealth());
	}
}

bool AEnemy::IsTargetable()
{
	return true;
}
