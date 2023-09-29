#include "BVAssetManager.h"
#include "BVGameplayTags.h"

UBVAssetManager& UBVAssetManager::Get()
{
	check(GEngine);

	UBVAssetManager* BVAssetManager = Cast<UBVAssetManager>(GEngine->AssetManager);
	return *BVAssetManager;
}

void UBVAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FBVGameplayTags::InitGameplayTags();
}
