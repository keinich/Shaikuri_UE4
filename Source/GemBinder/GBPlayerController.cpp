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

void AGBPlayerController::Tick(float deltaTime) {
  switch (_State) {
  case EGemBinderPlayerControllerState::OpenWorld:
    CheckForInteractables();
  case EGemBinderPlayerControllerState::Battle:
    return;
  }
}

void AGBPlayerController::OnPossess(APawn* InPawn) {
  Super::OnPossess(InPawn);

  FighterComponent->TrySetWorldCharacter(InPawn);

  AWorldCharacter* worldCharacter = Cast<AWorldCharacter, APawn>(InPawn);

  if (worldCharacter) {
    _State = EGemBinderPlayerControllerState::OpenWorld;
  }
  else {
    _State = EGemBinderPlayerControllerState::Battle;
  }
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

void AGBPlayerController::TryInteract() {
  if (_CurrentInteractable) {
    IInteractable::Execute_OnInteract(_CurrentInteractable, this);
  }
}

bool AGBPlayerController::TryGetActorTracingForward(FHitResult& hitResult) const {
  FVector start;
  FRotator rotation;

  GetPlayerViewPoint(start, rotation);
  FVector end = start + rotation.Vector() * TraceDistance;

  FCollisionQueryParams params;
  params.AddIgnoredActor(GetPawn());
  return GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECC_Camera, params);
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

void AGBPlayerController::CheckForInteractables() {
  FHitResult hitResult;
  AActor* hitActor = nullptr;
  if (TryGetActorTracingForward(hitResult)) {
    hitActor = hitResult.GetActor();
  }

  IInteractable* hitInteractable = nullptr;
  if (hitActor) {
    hitInteractable = Cast<IInteractable>(hitActor);
  }

  if (!hitInteractable) {
    if (_CurrentInteractable) {
      IInteractable::Execute_EndFocus(_CurrentInteractable, this);
      _CurrentInteractable = nullptr;
    }
  }
  else {
    if (!_CurrentInteractable) {
      IInteractable::Execute_StartFocus(hitActor, this);
      _CurrentInteractable = hitActor;
    }
    else if (_CurrentInteractable != hitActor) {
      IInteractable::Execute_EndFocus(_CurrentInteractable, this);
      IInteractable::Execute_StartFocus(hitActor, this);

      _CurrentInteractable = hitActor;
    }
  }

}
