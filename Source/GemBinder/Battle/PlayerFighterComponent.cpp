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
#include "Battle.h"


void UPlayerFighterComponent::StartPlacingBeast() {
  _IsPlacingGem = true;
}

void UPlayerFighterComponent::CancelPlacingBeast() {
  _IsPlacingGem = false;
  if (_Board) {
    _Board->UnhoverAllCells();
  }
}

void UPlayerFighterComponent::CancelPlacingGem() {
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
      HandleClickOnBoard(hitBoard, hitResult.Location);
    }
  }

}

void UPlayerFighterComponent::OnHoverMouse(float axisValue) {
  if (_IsPlacingGem) {
    TryHoverCell();
  }
}

void UPlayerFighterComponent::StartTurn() {
  Super::StartTurn();

  OnTurnStarted.Broadcast();
}

void UPlayerFighterComponent::EndTurn() {
  Super::EndTurn();

  OnTurnEnded.Broadcast();
}

void UPlayerFighterComponent::DrawStartingHand() {
  Super::DrawStartingHand();

}

void UPlayerFighterComponent::StartPlacingGem(FGemDefinition gemDefinition) {
  if (!_HasTurn) {
    UE_LOG(LogTemp, Warning, TEXT("Trying to place gem although not having turn"))
    return;
  }
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
    CancelPlacingGem();
    _Battle->PlaceGem(cellCoordinates, _GemToPlace);
    _Battle->SubmitTurn(this);
  }
  else {
    board->SelectCell(cellCoordinates.X, cellCoordinates.Y);
  }
}