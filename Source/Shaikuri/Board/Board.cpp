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
  _OuterCellRadiusCm = (2.0f / sqrt(3)) * InnerCellRadiusCm;
  for (int x = 0; x < NumberCellsX; ++x) {
    for (int y = 0; y < NumberCellsY; ++y) {
      bool evenRow = (FMath::Fmod(y, 2) == 0);
      float xOffset = InnerCellRadiusCm;
      if (evenRow) {
        xOffset = 0;
      }

      FTransform transform = FTransform(
        FVector(x * 2 * InnerCellRadiusCm + xOffset, y * 1.5f * _OuterCellRadiusCm, 0)
      );
      transform.SetScale3D(FVector(InnerCellRadiusCm / 100.0f));
      UBoardCellComponent* boardCellComponent = ConstructGridcell1(transform);
      boardCellComponent->Coordinates = FVector2D(x, y);
    }
  }
}

FVector2D ABoard::GetCellCoordinatesFromLocation3D(FVector location3D) {
  int xWorld = (int)location3D.X;
  int yWorld = (int)location3D.Y;
  int closestXLeft = xWorld - FMath::Fmod(xWorld, (int)InnerCellRadiusCm);
  int closestYBottom = yWorld - FMath::Fmod(yWorld, (int)(1.5 * _OuterCellRadiusCm));
  int closestXRight = closestXLeft + FMath::Sign(xWorld) * (int)InnerCellRadiusCm;
  int closestYTop = closestYBottom + FMath::Sign(yWorld) * (int)(1.5 * _OuterCellRadiusCm);

  FVector2D bottomLeft = FVector2D(closestXLeft, closestYBottom);
  FVector2D bottomRight = FVector2D(closestXRight, closestYBottom);
  FVector2D topLeft = FVector2D(closestXLeft, closestYTop);
  FVector2D topRight = FVector2D(closestXRight, closestYTop);

  FVector2D bottomLeftCoordinates;
  FVector2D bottomRightCoordinates;
  FVector2D topLeftCoordinates;
  FVector2D topRightCoordinates;

  TArray<FVector2D> candidates;
  TArray<FVector2D> candidateCoordinates;

  if (TryGetCoordinates(bottomLeft, bottomLeftCoordinates)) {
    candidates.Add(bottomLeft);
    candidateCoordinates.Add(bottomLeftCoordinates);
  }
  if (TryGetCoordinates(bottomRight, bottomRightCoordinates)) {
    candidates.Add(bottomLeft);
    candidateCoordinates.Add(bottomRightCoordinates);
  }
  if (TryGetCoordinates(topLeft, topLeftCoordinates)) {
    candidates.Add(topLeft);
    candidateCoordinates.Add(topLeftCoordinates);
  }
  if (TryGetCoordinates(topRight, topRightCoordinates)) {
    candidates.Add(topRight);
    candidateCoordinates.Add(topRightCoordinates);
  }

  float distanceToCanditate1 = FVector2D::Distance(candidates[0], FVector2D(location3D.X, location3D.Y));
  float distanceToCanditate2 = FVector2D::Distance(candidates[1], FVector2D(location3D.X, location3D.Y));
  if (distanceToCanditate1 < distanceToCanditate2) {
    return candidateCoordinates[0];
  }
  else {
    return candidateCoordinates[1];
  }
  return FVector2D(1.0f, 2.0f);
}

void ABoard::SelectCell(int x, int y) {

  if (_SelectedCellCoordinates.X >= 0) {
    UBoardCellComponent* currentlySelectedBoardCellComponent = GetBoardCell(
      _SelectedCellCoordinates.X, _SelectedCellCoordinates.Y
    );
    if (currentlySelectedBoardCellComponent) {
      SetCellUnselectedMesh(currentlySelectedBoardCellComponent);
    }
  }

  UBoardCellComponent* boardCellComponent = GetBoardCell(x, y);
  if (!boardCellComponent) {
    return;
  }

  _SelectedCellCoordinates = FVector2D(x, y);
  SetCellSelectedMesh(boardCellComponent);
}

bool ABoard::TryGetCoordinates(FVector2D centerWorldPositionXY, OUT FVector2D& coordinates) {
  bool evenRow = (FMath::Fmod(centerWorldPositionXY.Y, (int)(3 * _OuterCellRadiusCm)) == 0);
  if (evenRow) {
    if (FMath::Fmod(centerWorldPositionXY.X, (int)(2 * InnerCellRadiusCm)) == 0) {
      coordinates = FVector2D(
        centerWorldPositionXY.X / (int)(2 * InnerCellRadiusCm),
        centerWorldPositionXY.Y / (int)(1.5 * _OuterCellRadiusCm)
      );
      return true;
    }
    else {
      return false;
    }
  }
  else {
    if (FMath::Fmod((centerWorldPositionXY.X - InnerCellRadiusCm), (int)(2 * InnerCellRadiusCm)) == 0) {
      coordinates = FVector2D(
        (centerWorldPositionXY.X - InnerCellRadiusCm) / (int)(2 * InnerCellRadiusCm),
        centerWorldPositionXY.Y / (int)(1.5 * _OuterCellRadiusCm)
      );
      return true;
    }
    else {
      return false;
    }
  }
}
