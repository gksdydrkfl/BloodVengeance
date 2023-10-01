#include "Item/Weapon/Katana/Katana.h"
#include "Components/BoxComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "BloodVengeance/DebugMacro.h" 

AKatana::AKatana()
{
	CurrentCombo = 0;
	MaxCombo = 3;

	WeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollision"));
	WeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	WeaponCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	WeaponCollision->SetupAttachment(GetItemMesh());
}

void AKatana::BeginPlay()
{
	Super::BeginPlay();

	WeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &AKatana::WeaponCollisionOverlap);
}



void AKatana::SetCurrentCombo(int32 NewValue)
{
	CurrentCombo = NewValue;
}


void AKatana::WeaponCollisionOverlap(class UPrimitiveComponent* OnmComponentBeginVerlap, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Debug::Log(*OtherComp->GetName());
	if (HasAuthority())
	{
		if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			TargetASC->ApplyGameplayEffectSpecToSelf(*DemageEffectSpecHandle.Data.Get());
		}
	}
}

void AKatana::SetCollisionEnabled(const ECollisionEnabled::Type& NewType)
{
	WeaponCollision->SetCollisionEnabled(NewType);
}
