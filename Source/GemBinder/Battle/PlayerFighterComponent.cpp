// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerFighterComponent.h"

// Engine Includes
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

// Game Includes
#include "Gems/GemService.h"
#include "Board/BoardPawn.h"
#include "Board/Board.h"
#include "GBPlayerController.h"


void UPlayerFighterComponent::StartPlacingBeast() {
  _IsPlacingGem = true;
}

void UPlayerFighterComponent::CancelPlacingBeast() {
  _IsPlacingGem = false;
  if (_Board) {
    _Board->UnhoverAllCells();
  }
}

void UPlayerFighterComponent::OnLeftClick() {

  FHitResult hitResult;
  AGBPlayerController* playerController = (AGBPlayerController*)UGameplayStatics::GetPlayerController(this, 0);
  bool hitSomething = (playerController->TryGetActorUnderMouse(OUT hitResult));
  if (hitSomething) {
    ABoard* hitBoard = Cast<ABoard, AActor>(hitResult.Actor.Get());
    if (hitBoard) {
      GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Board was hit"));
      HandleClickOnBoard(hitBoard, hitResult.Location);
    }
  }

}

void UPlayerFighterComponent::OnHoverMouse(float axisValue) {
  if (_IsPlacingGem) {
    TryHoverCell();
  }
}

void UPlayerFighterComponent::DrawStartingHand() {

  // Testweise kompletten Beutel ziehen
  for (int i = 0; i <= Bag.Num(); ++i) {
    DrawNextGem();
  }

}

void UPlayerFighterComponent::StartPlacingGem(FGemDefinition gemDefinition) {
  _GemToPlace = gemDefinition;
  _IsPlacingGem = true;
}

void UPlayerFighterComponent::AfterGemDrawn(FGemDefinition gemDefinition) {
  //FTransform transform;
  //AGem* gem = AGemService::SpawnGem(transform, this);
  //ABoardPawn* pawn = (ABoardPawn*)UGameplayStatics::GetPlayerPawn(this,0);
  //pawn->PlaceGemInHand(gem);

  OnGemDrawn.Broadcast(gemDefinition);
}

void UPlayerFighterComponent::TryHoverCell() {
  FHitResult hitResult;
  AGBPlayerController* playerController = (AGBPlayerController*)UGameplayStatics::GetPlayerController(this, 0);
  bool hitSomething = (playerController->TryGetActorUnderMouse(OUT hitResult));
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

void UPlayerFighterComponent::HoverOverCell(ABoard* board, FVector locationOfClick3D) {
  FVector2D cellCoordinates = board->GetCellCoordinatesFromLocation3D(locationOfClick3D);
  board->HoverCell(cellCoordinates.X, cellCoordinates.Y);
}

void UPlayerFighterComponent::HandleClickOnBoard(ABoard* board, FVector locationOfClick3D) {
  FVector2D cellCoordinates = board->GetCellCoordinatesFromLocation3D(locationOfClick3D);
  if (_IsPlacingGem) {
    board->PlaceBeast(cellCoordinates.X, cellCoordinates.Y);
  }
  else {
    board->SelectCell(cellCoordinates.X, cellCoordinates.Y);
  }
}