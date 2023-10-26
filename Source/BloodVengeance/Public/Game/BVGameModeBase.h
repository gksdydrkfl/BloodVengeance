#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BVGameModeBase.generated.h"

class UCharacterClassInfo;

UCLASS()
class BLOODVENGEANCE_API ABVGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditAnywhere, Category = "Character Class Defaults", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;

public:

	UCharacterClassInfo* GetCharacterClassInfo() const { return CharacterClassInfo; }

};
