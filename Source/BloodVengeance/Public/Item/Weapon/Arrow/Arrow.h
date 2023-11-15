#pragma once

#include "CoreMinimal.h"
#include "Item/Weapon/Weapon.h"
#include "Arrow.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class BLOODVENGEANCE_API AArrow : public AWeapon
{
	GENERATED_BODY()
	
public:

	AArrow();

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UProjectileMovementComponent> Projectile;

	UPROPERTY(EditAnywhere, meta = (AllowPriavteAccess = true))
	TObjectPtr<USphereComponent> SphereCollision;

public:

	void SetActive(const bool& Value);

	void SetDirection(const FVector& NewDirection, const FVector& NewEnd);

};
