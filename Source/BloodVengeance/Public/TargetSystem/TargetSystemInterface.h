#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TargetSystemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTargetSystemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BLOODVENGEANCE_API ITargetSystemInterface
{
	GENERATED_BODY()

public:

	virtual bool IsTargetable() = 0;
};
