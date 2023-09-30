#include "Item/Item.h"

AItem::AItem()
{
	
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));

	RootComponent = ItemMesh;

	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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
