// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle.h"

// Engine Includes

// Game Includes
#include "FighterComponent.h"
#include "Board/Board.h"

#pragma region Engine Callbacks

// Sets default values
ABattle::ABattle() {
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABattle::BeginPlay() {
  Super::BeginPlay();

}

// Called every frame
void ABattle::Tick(float DeltaTime) {
  Super::Tick(DeltaTime);

}

#pragma endregion

void ABattle::Start(TArray<UFighterComponent*> fighters, ABoard* board) {
  _Fighters = fighters;
  _Board = board;

  for (int i = 0; i < fighters.Num(); ++i) {
    fighters[i]->StartBattle(this);
  }

  _FighterWhoHasTurn = fighters[0];
  _FighterWhoHasTurn->StartTurn();

}

void ABattle::PlaceGem(ABoard* board, FVector2D coordinates, FGemDefinition gemDefinition) {
  switch (gemDefinition.Type) {
  case EGemType::Beast:
    FTransform transform = board->GetCellTransform(coordinates.X, coordinates.Y);
    transform.AddToTranslation(FVector(0, 0, 500));
    FActorSpawnParameters spawnParams;
    spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    AActor* beast = GetWorld()->SpawnActor<AActor>(gemDefinition.GemActorClass, transform, spawnParams);
    //board->PlaceBeast(beast, coordinates.X, coordinates.Y);
  }

  // TODO move this to a SubmitTurn ?
  PassTurnToNextPlayer();

}

void ABattle::SubmitTurn(UFighterComponent* fighter) {
  int indexOfFighterWhoHasTurn = _Fighters.Find(_FighterWhoHasTurn);
  int indexOfFighter = _Fighters.Find(fighter);
  if (indexOfFighterWhoHasTurn == INDEX_NONE) {
    UE_LOG(LogTemp, Error, TEXT("Couldnt find fighter who has turn"));
    return;
  }
  if (indexOfFighter == INDEX_NONE) {
    UE_LOG(LogTemp, Error, TEXT("Couldnt find fighter who wants to submit turn"));
    return;
  }
  if (indexOfFighter != indexOfFighterWhoHasTurn) {
    UE_LOG(LogTemp, Error, TEXT("Invalid fighter who wants to submit turn"));
    return;
  }

  PassTurnToNextPlayer();

}

void ABattle::PassTurnToNextPlayer() {

  _FighterWhoHasTurn->EndTurn();

  int indexOfFighterWhoHasTurn = _Fighters.Find(_FighterWhoHasTurn);

  int newIndexOfFIghterWhoHasTurn = indexOfFighterWhoHasTurn + 1;
  if (newIndexOfFIghterWhoHasTurn >= _Fighters.Num()) {
    newIndexOfFIghterWhoHasTurn = 0;
  }
  _FighterWhoHasTurn = _Fighters[newIndexOfFIghterWhoHasTurn];

  _FighterWhoHasTurn->StartTurn();
}

