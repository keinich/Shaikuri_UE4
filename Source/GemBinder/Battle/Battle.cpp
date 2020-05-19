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

void ABattle::PlaceGem(FVector2D coordinates, FGemDefinition gemDefinition) {

  if (GetGemActorByCoordinates(coordinates)) {
    UE_LOG(LogTemp, Warning, TEXT("There is already a Gem on theses coordinates"));
    return;
  }

  AActor* gemActor = nullptr;

  switch (gemDefinition.Type) {
  case EGemType::Beast:
    FTransform transform = _Board->GetCellTransform(coordinates.X, coordinates.Y);
    transform.AddToTranslation(FVector(0, 0, 500));
    FActorSpawnParameters spawnParams;
    spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    gemActor = GetWorld()->SpawnActor<AActor>(gemDefinition.GemActorClass, transform, spawnParams);
  }

  if (gemActor) {
    AddGemActorToCoordinates(coordinates, gemActor);
  }
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

AActor* ABattle::GetGemActorByCoordinates(FVector2D coordinates) {
  FActorByInt* actorByInt = _GemActorsByCoordinates.Find(coordinates.X);
  if (!actorByInt) {
    return nullptr;
  }
  AActor** resultActorS = actorByInt->ActorByInt.Find(coordinates.Y);
  if (!resultActorS) {
    return nullptr;
  }
  return *resultActorS;

}

ABoard* ABattle::GetBoard() {
  return _Board;
}

void ABattle::AddGemActorToCoordinates(FVector2D coordinates, AActor* actor) {
    
  FActorByInt* actorByIntS = _GemActorsByCoordinates.Find(coordinates.X);
  FActorByInt actorByInt;
  if (!actorByIntS) {
    _GemActorsByCoordinates.Add(coordinates.X, actorByInt);
  }

  _GemActorsByCoordinates[coordinates.X].ActorByInt.Add(coordinates.Y, actor);

}

