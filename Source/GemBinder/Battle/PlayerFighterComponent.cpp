// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerFighterComponent.h"

// Engine Includes

// Game Includes
#include "Gems/GemService.h"

void UPlayerFighterComponent::DrawStartingHand() {

  // Testweise kompletten Beutel ziehen
  for (int i = 0; i < Bag.Num(); ++i) {
    DrawNextGem();
  }

}

void UPlayerFighterComponent::OnGemDrawn() {
  FTransform transform;
  AGem* gem = AGemService::SpawnGem(transform, this);
}
