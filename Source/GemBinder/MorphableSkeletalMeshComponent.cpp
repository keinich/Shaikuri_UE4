// Fill out your copyright notice in the Description page of Project Settings.


#include "MorphableSkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/Animation/MorphTarget.h"

UMorphableSkeletalMeshComponent::UMorphableSkeletalMeshComponent() {
  RecreateTraitsByMorph();
}

void UMorphableSkeletalMeshComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) {

  Super::PostEditChangeProperty(PropertyChangedEvent);

  FName PropertyThatChanged = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

  if (PropertyThatChanged == GET_MEMBER_NAME_CHECKED(UMorphableSkeletalMeshComponent, SkeletalMesh)) {
    RecreateTraitsByMorph();
  }

  if (PropertyThatChanged == GET_MEMBER_NAME_CHECKED(UMorphableSkeletalMeshComponent, TraitByMorph)) {
    RecreateMorphsByTrait();
  }

}

void UMorphableSkeletalMeshComponent::BeginPlay() {
  Super::BeginPlay();
  RecreateMorphsByTrait();
}

TArray<FName> UMorphableSkeletalMeshComponent::GetTraits() {
  if (MorphsByTrait.Num() == 0 && TraitByMorph.Num() > 0) {
    RecreateMorphsByTrait();
  }
  TArray<FName> result;
  MorphsByTrait.GetKeys(result);
  return result;
}

void UMorphableSkeletalMeshComponent::SetMorphByTrait(FName trait, FName morph) {
  if (!MorphsByTrait.Contains(trait)) {
    MorphsByTrait.Add(trait, FMorphs());
  }
  MorphsByTrait[trait].Morphs.AddUnique(morph);
}

void UMorphableSkeletalMeshComponent::SetTraitByMorph(FName morph, FName trait) {
  if (TraitByMorph.Contains(morph)) { // knownMorph must be a key in TraitByMorph
    TraitByMorph[morph] = trait; // set the trait for the morph
    SetMorphByTrait(trait, morph);
  }
}

void UMorphableSkeletalMeshComponent::RecreateMorphsByTrait() {

  //TODO Cache this, so when a already known Mesh is set, you still have your old mappings
  MorphsByTrait.Reset();
  for (auto traitByMorph : TraitByMorph) {
    if (traitByMorph.Value != TEXT("")) {
      SetMorphByTrait(traitByMorph.Value, traitByMorph.Key);
    }
  }
}

void UMorphableSkeletalMeshComponent::RecreateTraitsByMorph() {

  //TODO Cache this, so when a already known Mesh is set, you still have your old mappings
  TraitByMorph.Reset();
  if (SkeletalMesh) {
    auto morphTargets = this->SkeletalMesh->MorphTargets;
    for (UMorphTarget* morphTarget : morphTargets) {
      TraitByMorph.Add(morphTarget->GetFName(), morphTarget->GetFName());
    }
  }
}