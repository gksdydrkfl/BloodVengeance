#include "Item/Weapon/Arrow/Arrow.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"


#include "BloodVengeance/DebugMacro.h"

AArrow::AArrow()
{
	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SphereCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
	SphereCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Block);
	SetRootComponent(SphereCollision);

	GetItemMesh()->SetupAttachment(SphereCollision);
	GetItemMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Projectile->SetUpdatedComponent(SphereCollision);
	
	Projectile->InitialSpeed = 3000.f;
	Projectile->MaxSpeed = 3000.f;
}

void AArrow::BeginPlay()
{
	Super::BeginPlay();


}

void AArrow::SetActive(const bool& Value)
{
	if (Projectile == nullptr)
	{
		return;
	}

	//Projectile->SetAutoActivate(Value);
	Projectile->Activate(Value);
}

void AArrow::SetDirection(const FVector& NewDirection, const FVector& NewEnd)
{
	if (Projectile == nullptr)
	{
		return;
	}

	Projectile->Velocity = NewDirection * Projectile->InitialSpeed;
	DRAW_LINE(GetActorLocation(), NewEnd)
}
