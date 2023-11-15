// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Weapon/Weapon.h"
#include "Bow.generated.h"

/**
 * 
 */
UCLASS()
class BLOODVENGEANCE_API ABow : public AWeapon
{
	GENERATED_BODY()
	
public:

	ABow();

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemProperties", meta = (AllowPrivateAccess = true))
	TObjectPtr<USkeletalMeshComponent> ItemSkeletalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ItemProperties", meta = (AllowPrivateAccess = true))
	bool bGrabString;

public:

	USkeletalMeshComponent* GetMesh() const { return ItemSkeletalMesh; }

	UFUNCTION(BlueprintCallable)
	bool GetGrabString() const { return bGrabString; };
	UFUNCTION(BlueprintCallable)
	void SetGrabString(bool NewValue) { bGrabString = NewValue; }

};
