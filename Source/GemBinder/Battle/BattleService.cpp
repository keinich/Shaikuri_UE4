// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleService.h"

// Engine Includes
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "GameFramework/GameState.h"
#include "Kismet/GameplayStatics.h"

// Game Includes
#include "Board/BoardPawn.h"
#include "Board/BattleGameModeBase.h"
#include "GBGameStateBase.h"

#pragma region Engine Callbacks

// Sets default values
ABattleService::ABattleService() {
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABattleService::BeginPlay() {
  Super::BeginPlay();

}

// Called every frame
void ABattleService::Tick(float DeltaTime) {
  Super::Tick(DeltaTime);

}

#pragma endregion

void ABattleService::StartBattleInternal() {

  // Change Pawn
  APlayerController* playerController = GetWorld()->GetFirstPlayerController();
  APawn* pawn = playerController->GetPawn();
  FTransform transform = pawn->GetTransform();
  pawn->Destroy();
  transform.AddToTranslation(FVector(0, 0, 100.0f));
  ABoardPawn* boardPawn = SpawnBoardPawn(transform);
  playerController->Possess(boardPawn);

  // Change Hud
  ABattleGameModeBase* gameMode = (ABattleGameModeBase*)UGameplayStatics::GetGameMode(this);
  gameMode->SetHud(CreateBattleHud());

}

void ABattleService::StartBattle(const UObject* worldContextObject) {
  return AGBGameStateBase::GetBattleService(worldContextObject)->StartBattleInternal();
}
