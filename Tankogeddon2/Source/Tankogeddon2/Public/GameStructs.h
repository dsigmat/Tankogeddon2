#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameStructs.generated.h"

UENUM(BlueprintType)
enum class ECannonType : uint8
{
	FireProjectile = 0,
	FireTrace = 1
};


UCLASS()
class TANKOGEDDON2_API UGameStructs : public UObject
{
	GENERATED_BODY()
	
};
