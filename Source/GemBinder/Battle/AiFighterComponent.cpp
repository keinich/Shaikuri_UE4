// Fill out your copyright notice in the Description page of Project Settings.

#include "AiFighterComponent.h"
// Engine Includes

// Game Includes
#include "Battle.h"
#include "Board/Board.h"

void UAiFighterComponent::StartTurn() {
  Super::StartTurn();

  TArray<FVector2D> coordinates = _Battle->GetBoard()->GetCellCoordinates();

  for (int i = 0; i < coordinates.Num(); ++i) {
    if (!_Battle->GetGemActorByCoordinates(coordinates[i])) {
      _Battle->PlaceGem(coordinates[i], _Hand[0]);
      _Battle->SubmitTurn(this);
      return;
    }
  }

}