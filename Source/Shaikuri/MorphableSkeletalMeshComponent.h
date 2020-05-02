// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "MorphableSkeletalMeshComponent.generated.h"

USTRUCT()
struct FMorphs {
  GENERATED_BODY()

    TArray<FName> Morphs;
};

/**
 * 
 */
UCLASS()
class SHAIKURI_API UMorphableSkeletalMeshComponent : public USkeletalMeshComponent
{
  GENERATED_BODY()

    friend class MeshTraitsComponent;

public: // Functions

  UMorphableSkeletalMeshComponent();

  virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

  virtual void BeginPlay() override;

  UFUNCTION(BlueprintCallable, Category = "Traits")
    TArray<FName> GetTraits();

  void SetMorphByTrait(FName trait, FName morph);
  void SetTraitByMorph(FName morph, FName trait);

public: // Fields

  TMap<FName, FMorphs> MorphsByTrait;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traits")
    TMap<FName, FName> TraitByMorph;

protected: // Functions

  void RecreateTraitsByMorph();
  void RecreateMorphsByTrait();

};
