// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"

#include "Board.h"

// Engine Includes

// Game Includes

#include "BoardCellComponent.h"

#pragma region Engine Callbacks

// Sets default values
ABoard::ABoard() {
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

}

void ABoard::OnConstruction(const FTransform& Transform) {
  RecreateGrid();
}

// Called when the game starts or when spawned
void ABoard::BeginPlay() {
  Super::BeginPlay();
}

// Called every frame
void ABoard::Tick(float DeltaTime) {
  Super::Tick(DeltaTime);

}
#pragma endregion

void ABoard::RecreateGrid() {
  float outerCellRadius = (2.0f / sqrt(3)) * InnerCellRadiusCm;
  for (int x = 0; x < NumberCellsX; ++x) {
    for (int y = 0; y < NumberCellsY; ++y) {
      bool evenRow = (FMath::Fmod(y, 2) == 0);
      float xOffset = InnerCellRadiusCm;
      if (evenRow) {
        xOffset = 0;
      }

      FTransform transform = FTransform(FVector(x * 2 * InnerCellRadiusCm + xOffset, y * 1.5f * outerCellRadius, 0));
      transform.SetScale3D(FVector(InnerCellRadiusCm / 100.0f));
      UBoardCellComponent* boardCellComponent = ConstructGridcell1(transform);
      _BoardCells.Add(boardCellComponent);
    }
  }
}

FVector2D ABoard::GetCellCoordinatesFromLocation3D(FVector location3D) {
  return FVector2D();
}

void ABoard::SetCellSelected(bool isSelected, int x, int y) {
  UBoardCellComponent* boardCellComponent = GetBoardCell(x, y);
  if (!boardCellComponent) {
    return;
  }
  SetCellSelectedMesh(boardCellComponent);
}

UBoardCellComponent* ABoard::GetBoardCell(int x, int y) {
  // TODO implement coordinat system
  if (_BoardCells.Num() == 0) {
    return nullptr;
  }
  return _BoardCells[0];
}
