// Fill out your copyright notice in the Description page of Project Settings.

#include "AiFighterComponent.h"
// Engine Includes

// Game Includes
#include "Battle.h"

void UAiFighterComponent::StartTurn() {
  Super::StartTurn();

  _Battle->SubmitTurn(this);

}