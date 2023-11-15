#include "Item/Item.h"

AItem::AItem()
{
	ItemStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));

	ItemStaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

}

void AItem::SetItemName()
{
}

void AItem::SetItemDesc()
{
}
