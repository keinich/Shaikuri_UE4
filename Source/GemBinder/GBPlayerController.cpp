// Fill out your copyright notice in the Description page of Project Settings.


#include "GBPlayerController.h"

// Engine Includes
#include "Engine/World.h"
#include "Engine/Engine.h"

// Game Includes
#include "Board/Board.h"
#include "Battle/PlayerFighterComponent.h"

#pragma region Engine Callbacks

AGBPlayerController::AGBPlayerController() {

  FighterComponent = CreateDefaultSubobject<UPlayerFighterComponent>(FName("Fighter Component"));

}

void AGBPlayerController::BeginPlay() {
  Super::BeginPlay();
 
}

#pragma endregion

void AGBPlayerController::StartPlacingBeast() {
  _IsPlacingBeast = true;
}

void AGBPlayerController::CancelPlacingBeast() {
  _IsPlacingBeast = false;
  if (_Board) {
    _Board->UnhoverAllCells();
  }
}

void AGBPlayerController::OnLeftClick() {

  FHitResult hitResult;
  bool hitSomething = (TryGetActorUnderMouse(OUT hitResult));
  if (hitSomething) {
    ABoard* hitBoard = Cast<ABoard, AActor>(hitResult.Actor.Get());
    if (hitBoard) {
      GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Board was hit"));
      HandleClickOnBoard(hitBoard, hitResult.Location);
    }
  }

}

void AGBPlayerController::OnHoverMouse(float axisValue) {
  if (_IsPlacingBeast) {
    TryHoverCell();
  }
}

void AGBPlayerController::TryHoverCell() {
  FHitResult hitResult;
  bool hitSomething = (TryGetActorUnderMouse(OUT hitResult));
  if (hitSomething) {
    ABoard* hitBoard = Cast<ABoard, AActor>(hitResult.Actor.Get());
    if (hitBoard) {
      //TODO think of better way to get a ref to the board...
      _Board = hitBoard;
      HoverOverCell(hitBoard, hitResult.Location);
    }
    else {
      if (_Board) {
        _Board->UnhoverAllCells();
      }
    }
  }
}

bool AGBPlayerController::TryGetActorUnderMouse(OUT FHitResult& hitResult) const {
  float mousePositionX;
  float mousePositionY;
  bool gotMousePosition = GetMousePosition(mousePositionX, mousePositionY);
  if (!gotMousePosition) {
    return false;
  }

  FVector2D screenLocationOfCrosshair = FVector2D(
    mousePositionX, mousePositionY
  );

  // "De-project" the screen position of the crosshair to a world direction
  FVector lookDirection;
  if (TryGetLookDirection(screenLocationOfCrosshair, OUT lookDirection)) {
    // Line-Trace along that look direction and see waht we hit (up to max range)
    return (TryGetActorInLookDirection(lookDirection, OUT hitResult));
  }
  else {
    return false;
  }
}

bool AGBPlayerController::TryGetLookDirection(
  FVector2D screenPosition,
  OUT FVector& lookDirection
) const {
  FVector worldPositionOfCrossHairOnViewCamera; // To be discarded
  return DeprojectScreenPositionToWorld(
    screenPosition.X,
    screenPosition.Y,
    OUT worldPositionOfCrossHairOnViewCamera,
    OUT lookDirection
  );
}

bool AGBPlayerController::TryGetActorInLookDirection(FVector lookDirection, OUT FHitResult& hitResult) const {
  FVector startLocation = PlayerCameraManager->GetCameraLocation();
  FVector endLocation = startLocation + (lookDirection * 1000000.0f);
  FCollisionObjectQueryParams params = FCollisionObjectQueryParams();
  if (
    GetWorld()->LineTraceSingleByChannel(
      hitResult,
      startLocation,
      endLocation,
      ECC_Camera
    )
    ) {
    return true;
  }
  else {
    return false;
  }
}

void AGBPlayerController::HoverOverCell(ABoard* board, FVector locationOfClick3D) {
  FVector2D cellCoordinates = board->GetCellCoordinatesFromLocation3D(locationOfClick3D);
  board->HoverCell(cellCoordinates.X, cellCoordinates.Y);
}

void AGBPlayerController::HandleClickOnBoard(ABoard* board, FVector locationOfClick3D) {
  FVector2D cellCoordinates = board->GetCellCoordinatesFromLocation3D(locationOfClick3D);
  if (_IsPlacingBeast) {
    board->PlaceBeast(cellCoordinates.X, cellCoordinates.Y);
  }
  else {
    board->SelectCell(cellCoordinates.X, cellCoordinates.Y);
  }
}