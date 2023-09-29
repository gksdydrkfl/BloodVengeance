#include "Item/Item.h"

AItem::AItem()
{
	
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	SetRootComponent(ItemMesh);

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
