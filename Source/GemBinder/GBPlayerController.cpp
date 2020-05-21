// Fill out your copyright notice in the Description page of Project Settings.


#include "GBPlayerController.h"

// Engine Includes

// Game Includes

#pragma region Engine Callbacks

AGBPlayerController::AGBPlayerController() {

  FighterComponent = CreateDefaultSubobject<UPlayerFighterComponent>(FName("Fighter Component"));

}

void AGBPlayerController::BeginPlay() {
  Super::BeginPlay();
 
}

void AGBPlayerController::OnPossess(APawn* InPawn) {
  Super::OnPossess(InPawn);

  FighterComponent->TrySetWorldCharacter(InPawn);
}

#pragma endregion


bool AGBPlayerController::TryGetActorUnderMouse(FHitResult& hitResult) const {
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
  if (TryGetLookDirection(screenLocationOfCrosshair, lookDirection)) {
    // Line-Trace along that look direction and see waht we hit (up to max range)
    return (TryGetActorInLookDirection(lookDirection, hitResult));
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

bool AGBPlayerController::TryGetActorInLookDirection(FVector lookDirection, FHitResult& hitResult) const {
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
