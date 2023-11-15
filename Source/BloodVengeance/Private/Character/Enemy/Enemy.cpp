#include "Character/Enemy/Enemy.h"
#include "GAS/BVAbilitySystemComponent.h"
#include "GAS/BVAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "UI/Enemy/Widget/EnemyHealthBarWidget.h"
#include "BVGameplayTags.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS/BVBlueprintFunctionLibrary.h"
#include "Item/Weapon/Katana/Katana.h"
#include "Item/Weapon/Bow/Bow.h"
#include "AI/AIState.h"

//#include "AI/PatrolRoute.h"

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

	bHitReacting = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;

}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	InitAbilityActorInfo();

	if (AbilitySystemComponent == nullptr)
	{
		return;
	}

	UBVBlueprintFunctionLibrary::GiveStartupAbilities(this, AbilitySystemComponent, CharacterClass);

	UBVAttributeSet* Attribute = Cast<UBVAttributeSet>(AttributeSet);
	if (Attribute)
	{
		HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			AttributeSet->GetHealthAttribute()).AddUObject(this, &AEnemy::HealthChanged);

		AttributeSet->OnDeathStarted.AddDynamic(this, &AEnemy::OnDeathStarted);
	}

	AbilitySystemComponent->RegisterGameplayTagEvent(FBVGameplayTags::Get().Effects_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(
		this,
		&AEnemy::HitReactTagChanged
	);
	
}

void AEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!HasAuthority())
	{
		return;
	}

}

void AEnemy::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
}

void AEnemy::SetMovementSpeed(const EAIMovementState& NewAIState)
{
	float Speed = 0.f;

	switch (NewAIState)
	{
	case EAIMovementState::AIMS_Idle:
		Speed = 0.f;
		break;
	case EAIMovementState::AIMS_Walking:
		Speed = 150.f;
		break;
	case EAIMovementState::AIMS_Jogging:
		Speed = 300.f;
		break;
	case EAIMovementState::AIMS_Sprinting:
		Speed = 500.f;
		break;
	}

	GetCharacterMovement()->MaxWalkSpeed = Speed;
}

void AEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	InitializeDefaultAttributes();
}

void AEnemy::InitializeDefaultAttributes() const
{
	UBVBlueprintFunctionLibrary::InitializeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
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

void AEnemy::OnDeathStarted(AActor* NewActor)
{
	if(GetDeathMontage() != nullptr)
	{
		GetMesh()->GetAnimInstance()->Montage_Play(GetDeathMontage());
	}
}

void AEnemy::Die()
{
	//SetLifeSpan(LifeSpan);
	Super::Die();
}

