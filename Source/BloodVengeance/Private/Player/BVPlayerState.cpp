#include "Player/BVPlayerState.h"
#include "Gas/BVAbilitySystemComponent.h"
#include "Gas/BVAttributeSet.h"

ABVPlayerState::ABVPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UBVAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UBVAttributeSet>(TEXT("AttributeSet"));

	NetUpdateFrequency = 100.f;
}

UAbilitySystemComponent* ABVPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
