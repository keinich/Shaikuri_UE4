// Your copyright
#pragma once

// Engine Includes
#include "Engine/Texture.h"

// Last Include
#include "GemDefinition.generated.h" // this must be last include in the file

USTRUCT()
struct FGemDefinition
{
    GENERATED_USTRUCT_BODY()
    // add stuff you'd like to

public:

  UPROPERTY(EditAnywhere, category = "Gem")
    FName Name;

  UPROPERTY(EditAnywhere, category = "Gem")
    UTexture* Image;

  UPROPERTY(EditAnywhere, category = "Gem")
    FString Description;

};