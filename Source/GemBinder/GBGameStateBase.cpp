// Fill out your copyright notice in the Description page of Project Settings.

#include "GBGameStateBase.h"

// Engine Includes
#include "Kismet/GameplayStatics.h"

// Game Includes

#pragma region Engine Callbacks

void AGBGameStateBase::BeginPlay() {
  InitServices();
}

#pragma endregion

ABattleService* AGBGameStateBase::GetBattleService(const UObject* worldContextObject) {
  AGBGameStateBase* gameState = (AGBGameStateBase*)UGameplayStatics::GetGameState(worldContextObject);

  if (!gameState) {
    UE_LOG(LogTemp, Error, TEXT("Couldnt get GameState"));
    return nullptr;
  }

  return gameState->BattleService;
}

AGemService* AGBGameStateBase::GetGemService(const UObject* worldContextObject) {
  AGBGameStateBase* gameState = (AGBGameStateBase*)UGameplayStatics::GetGameState(worldContextObject);

  if (!gameState) {
    UE_LOG(LogTemp, Error, TEXT("Couldnt get GameState"));
    return nullptr;
  }

  return gameState->GemService;
}

AInteractionService* AGBGameStateBase::GetInteractionService(const UObject* worldContextObject) {
  AGBGameStateBase* gameState = (AGBGameStateBase*)UGameplayStatics::GetGameState(worldContextObject);

  if (!gameState) {
    UE_LOG(LogTemp, Error, TEXT("Couldnt get GameState"));
    return nullptr;
  }

  return gameState->InteractionService;
}
