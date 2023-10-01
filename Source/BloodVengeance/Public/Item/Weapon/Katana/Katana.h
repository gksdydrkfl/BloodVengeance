#pragma once

#include "CoreMinimal.h"
#include "Item/Weapon/Weapon.h"
#include "GameplayEffectTypes.h"
#include "Katana.generated.h"

class UBoxComponent;

UCLASS()
class BLOODVENGEANCE_API AKatana : public AWeapon
{
	GENERATED_BODY()

public:

	AKatana();

protected:

	virtual void BeginPlay() override;

private:

	int32 CurrentCombo;

	int32 MaxCombo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision", meta = (AllowPrivateAccess = true))
	UBoxComponent* WeaponCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect", meta = (AllowPrivateAccess = true))
	FGameplayEffectSpecHandle DemageEffectSpecHandle;

public:

	int32 GetCurrentCombo() { return CurrentCombo; }

	int32 GetMaxCombo() { return MaxCombo; }

	void SetCurrentCombo(int32 NewValue);

	void ResetCombo() { CurrentCombo = 0; }

	void SetDamageEffectSpecHandle(const FGameplayEffectSpecHandle& NewSpecHandle) { DemageEffectSpecHandle = NewSpecHandle; }

	UFUNCTION()
	void WeaponCollisionOverlap(class UPrimitiveComponent* OnmComponentBeginVerlap, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SetCollisionEnabled(const ECollisionEnabled::Type& NewType);

};
