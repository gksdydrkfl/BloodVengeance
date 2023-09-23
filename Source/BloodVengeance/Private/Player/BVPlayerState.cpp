#include "Player/BVPlayerState.h"
#include "Gas/BVAbilitySystemComponent.h"
#include "Gas/BVAttributeSet.h"
#include "Player/AidenPlayerController.h"
#include "UI/HUD/BVMainHUD.h"

ABVPlayerState::ABVPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UBVAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UBVAttributeSet>(TEXT("AttributeSet"));

	NetUpdateFrequency = 100.f;
}

void ABVPlayerState::BeginPlay()
{
	HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AttributeSet->GetHealthAttribute()).AddUObject(this, &ABVPlayerState::HealthChanged);
	MaxHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AttributeSet->GetMaxHealthAttribute()).AddUObject(this, &ABVPlayerState::MaxHealthChanged);
	StaminaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AttributeSet->GetStaminaAttribute()).AddUObject(this, &ABVPlayerState::StaminaChanged);
	MaxStaminaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AttributeSet->GetMaxStaminaAttribute()).AddUObject(this, &ABVPlayerState::MaxStaminaChanged);
}

UAbilitySystemComponent* ABVPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

float ABVPlayerState::GetHealth() const
{
	return AttributeSet->GetHealth();
}

float ABVPlayerState::GetMaxHealth() const
{
	return AttributeSet->GetMaxHealth();
}

float ABVPlayerState::GetStamina() const
{
	return AttributeSet->GetStamina();
}

float ABVPlayerState::GetMaxStamina() const
{
	return AttributeSet->GetMaxStamina();
}

void ABVPlayerState::HealthChanged(const FOnAttributeChangeData& Data)
{
	float Health = Data.NewValue;

	AAidenPlayerController* AidenPLayerController = Cast<AAidenPlayerController>(GetOwner());
	if (AidenPLayerController)
	{
		ABVMainHUD* MainHUD = AidenPLayerController->GetMainHUD();
		if (MainHUD)
		{
			MainHUD->UpdateHealthBar(Health / GetMaxHealth());
		}
	}
}

void ABVPlayerState::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
	float Health = Data.NewValue;

	AAidenPlayerController* AidenPLayerController = Cast<AAidenPlayerController>(GetOwner());
	if (AidenPLayerController)
	{
		ABVMainHUD* MainHUD = AidenPLayerController->GetMainHUD();
		if (MainHUD)
		{
			MainHUD->UpdateHealthBar(GetHealth() / Health);
		}
	}
}

void ABVPlayerState::StaminaChanged(const FOnAttributeChangeData& Data)
{
	float Stamina = Data.NewValue;

	AAidenPlayerController* AidenPLayerController = Cast<AAidenPlayerController>(GetOwner());
	if (AidenPLayerController)
	{
		ABVMainHUD* MainHUD = AidenPLayerController->GetMainHUD();
		if (MainHUD)
		{
			MainHUD->UpdateStaminaBar(Stamina / GetMaxStamina());
		}
	}
}

void ABVPlayerState::MaxStaminaChanged(const FOnAttributeChangeData& Data)
{
	float Stamina = Data.NewValue;

	AAidenPlayerController* AidenPLayerController = Cast<AAidenPlayerController>(GetOwner());
	if (AidenPLayerController)
	{
		ABVMainHUD* MainHUD = AidenPLayerController->GetMainHUD();
		if (MainHUD)
		{
			MainHUD->UpdateHealthBar(GetStamina() / Stamina);
		}
	}
}
