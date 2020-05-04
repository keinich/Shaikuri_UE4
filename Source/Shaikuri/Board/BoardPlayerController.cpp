// Fill out your copyright notice in the Description page of Project Settings.

#include "BoardPlayerController.h"

// Engine Includes

#include "Engine/World.h"
#include "Engine/Engine.h"

// Game Includes

#include "Board.h"

#pragma region Engine Callbacks

void ABoardPlayerController::BeginPlay() {
  Super::BeginPlay();

  InputComponent->BindAction("LeftClick", EInputEvent::IE_Released, this, &ABoardPlayerController::OnLeftClick);
}

#pragma endregion

void ABoardPlayerController::OnLeftClick() {

  int32 ViewportSizeX, ViewportSizeY;
  GetViewportSize(ViewportSizeX, ViewportSizeY);
  float mousePositionX;
  float mousePositionY;
  bool gotMousePosition = GetMousePosition(mousePositionX, mousePositionY);
  if (!gotMousePosition) {
    return;
  }

  FVector2D screenLocationOfCrosshair = FVector2D(
    mousePositionX, mousePositionY
  );

  // "De-project" the screen position of the crosshair to a world direction
  FVector lookDirection;
  if (TryGetLookDirection(screenLocationOfCrosshair, OUT lookDirection)) {
    // Line-Trace along that look direction and see waht we hit (up to max range)
    FHitResult hitResult;
    bool hitSomething = (TryGetClickedActor(lookDirection, OUT hitResult));
    if (hitSomething) {
      ABoard* hitBoard = Cast<ABoard, AActor>(hitResult.Actor.Get());
      if (hitBoard) {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Board was hit"));
        HandleClickOnBoard(hitBoard, hitResult.Location);
      }
    }
  }
  else {
    return;
  }

}

bool ABoardPlayerController::TryGetLookDirection(
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

bool ABoardPlayerController::TryGetClickedActor(FVector lookDirection, OUT FHitResult& hitResult) const {
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

void ABoardPlayerController::HandleClickOnBoard(ABoard* board, FVector locationOfClick3D) {
  FVector2D cellCoordinates = board->GetCellCoordinatesFromLocation3D(locationOfClick3D);
  board->SelectCell(cellCoordinates.X, cellCoordinates.Y);
}
