// Fill out your copyright notice in the Description page of Project Settings.


#include "MeshTraitsComponent.h"
#include "MorphableSkeletalMeshComponent.h"

// Sets default values for this component's properties
UMeshTraitsComponent::UMeshTraitsComponent() {
  // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
  // off to improve performance if you don't need them.
  PrimaryComponentTick.bCanEverTick = true;

  MyOwner = this->GetOwner();
  if (MyOwner)
    MyOwnerName = FName(*MyOwner->GetName());
}


// Called when the game starts
void UMeshTraitsComponent::BeginPlay() {
  Super::BeginPlay();

  // ...

}


// Called every frame
void UMeshTraitsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

  // ...
}

void UMeshTraitsComponent::SetTrait(FName traitName, float amount) {

  if (TraitAmounts.Contains(traitName)) {
    TraitAmounts[traitName] = amount;
  }
  else {
    TraitAmounts.Add(traitName, amount);
  }

  if (!(this->GetOwner()))
    return;

  TArray<UMorphableSkeletalMeshComponent*> meshComponents;
  TArray<UMorphableSkeletalMeshComponent*> unmappedMeshComponentes;

  this->GetOwner()->GetComponents<UMorphableSkeletalMeshComponent>(meshComponents);

  for (UMorphableSkeletalMeshComponent* meshComponent : meshComponents) {
    if (meshComponent->SkeletalMesh) {
      if (meshComponent->MorphsByTrait.Contains(traitName)) {
        TArray<FName> morphNames = meshComponent->MorphsByTrait[traitName].Morphs; //Get MorphNames for the trait in the mesh
        for (FName morphName : morphNames) {
          meshComponent->SetMorphTarget(morphName, amount); //Applay morph for each morph name in the mesh

          /// Add the morphName to the known morphs for the trait
          if (!KnownMorphsByTrait.Contains(traitName))
            KnownMorphsByTrait.Add(traitName, FKnownMorphs());
          KnownMorphsByTrait[traitName].Morphs.AddUnique(morphName);
        }
      }
      else {
        unmappedMeshComponentes.Add(meshComponent);
      }
    }
  }

  /// propagade all knownMorphs for the trait down to the meshComponents
  if (KnownMorphsByTrait.Contains(traitName)) {
    for (UMorphableSkeletalMeshComponent* meshComponent : unmappedMeshComponentes) {
      for (FName knownMorph : KnownMorphsByTrait[traitName].Morphs) {
        meshComponent->SetTraitByMorph(knownMorph, traitName);
        meshComponent->SetMorphTarget(knownMorph, amount);
      }
    }
  }

}

TArray<FName> UMeshTraitsComponent::GetTraits() {

  TArray<FName> result;
  TMap<FName, FName> result1;

  TArray<UMorphableSkeletalMeshComponent*> meshComponents;

  this->GetOwner()->GetComponents<UMorphableSkeletalMeshComponent>(meshComponents);

  for (UMorphableSkeletalMeshComponent* comp : meshComponents) {
    for (FName trait : comp->GetTraits()) {
      if (!result1.Contains(trait)) {
        result1.Add(trait, trait);
      }
    }
  }

  result1.GetKeys(result);
  return result;
}

