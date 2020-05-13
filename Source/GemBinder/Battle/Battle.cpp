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

void ABattle::Start(TArray<UFighterComponent*> fighters) {
  _Fighters = fighters;

  for (int i = 0; i < fighters.Num(); ++i) {
    fighters[i]->StartBattle(this);
  }

}

void ABattle::PlaceGem(ABoard* board, FVector2D coordinates, FGemDefinition gemDefinition) {
  switch (gemDefinition.Type) {
  case EGemType::Beast:
    FTransform transform = board->GetCellTransform(coordinates.X, coordinates.Y);    
    AActor* beast = GetWorld()->SpawnActor(gemDefinition.GemActorClass, &transform);
    //board->PlaceBeast(beast, coordinates.X, coordinates.Y);
  }
}

