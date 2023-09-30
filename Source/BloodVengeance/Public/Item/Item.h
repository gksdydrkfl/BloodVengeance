#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"



UCLASS()
class BLOODVENGEANCE_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemProperties", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* ItemMesh;

	FString ItemName;

	FString ItemDesc;

public:

	virtual void SetItemName();

	virtual void SetItemDesc();
};
