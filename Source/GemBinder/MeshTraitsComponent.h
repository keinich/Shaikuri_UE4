// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MeshTraitsComponent.generated.h"

USTRUCT()
struct FKnownMorphs {
  GENERATED_BODY()

    TArray<FName> Morphs;
};


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHAIKURI_API UMeshTraitsComponent : public UActorComponent {
  GENERATED_BODY()

public: // Functions

  // Sets default values for this component's properties
  UMeshTraitsComponent();

  // Called every frame
  virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

  UFUNCTION(BlueprintCallable, Category = "Traits")
    void SetTrait(FName traitName, float amount);

  UFUNCTION(BlueprintCallable, Category = "Traits")
    TArray<FName> GetTraits();

public: // Fields

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traits")
    TArray<FName> Traits;

  TMap<FName, FKnownMorphs> KnownMorphsByTrait;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traits")
    TMap<FName, float> TraitAmounts;

  AActor* MyOwner;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Traits")
    FName MyOwnerName;

protected: // Functions

  // Called when the game starts
  virtual void BeginPlay() override;

};
