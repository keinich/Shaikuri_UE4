// Your copyright
#pragma once

// Engine Includes
#include "Engine/Texture.h"

// Last Include
#include "GemDefinition.generated.h" // this must be last include in the file

USTRUCT(Blueprintable, BlueprintType)
struct FGemDefinition
{
    GENERATED_USTRUCT_BODY()
    // add stuff you'd like to

public:

  UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Gem")
    FName Name;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Gem")
    UTexture* Image;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Gem")
    FText Description;

};