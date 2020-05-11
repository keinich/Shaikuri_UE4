// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleService.h"

// Engine Includes
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "GameFramework/GameState.h"
#include "Kismet/GameplayStatics.h"

// Game Includes
#include "Board/BoardPawn.h"
#include "GBGameModeBase.h"
#include "GBGameStateBase.h"
#include "Battle.h"
#include "GBPlayerController.h"

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

void ABattleService::StartBattleInternal(TArray<UFighterComponent*> fighters) {

  // Instantiate Battle
  ABattle* battle = CreateBattle();
  battle->Start(fighters);

}

void ABattleService::StartBattlePlayerAgainsOpponentsInternal(TArray<UFighterComponent*> opponents) {

  // Add Player as a fighter
  AGBPlayerController* playerController = (AGBPlayerController*)UGameplayStatics::GetPlayerController(this, 0);
  UPlayerFighterComponent* fighterComponent = playerController->FighterComponent;
  opponents.Add(fighterComponent);

  // Create the HUD for the player
  AGBGameModeBase* gameMode = (AGBGameModeBase*)UGameplayStatics::GetGameMode(this);
  gameMode->SetHud(CreateBattleHud(fighterComponent));

  // Change Pawn
  APawn* pawn = playerController->GetPawn();
  FTransform transform = pawn->GetTransform();
  pawn->Destroy();
  transform.AddToTranslation(FVector(0, 0, 100.0f));
  ABoardPawn* boardPawn = SpawnBoardPawn(transform);
  playerController->Possess(boardPawn);

  StartBattleInternal(opponents);
}

void ABattleService::StartBattle(TArray<UFighterComponent*> fighters, const UObject* worldContextObject) {
  return AGBGameStateBase::GetBattleService(worldContextObject)->StartBattleInternal(fighters);
}

void ABattleService::StartBattlePlayerAgainstOpponents(
  TArray<UFighterComponent*> opponents, const UObject* worldContextObject
) {
  AGBGameStateBase::GetBattleService(worldContextObject)->StartBattlePlayerAgainsOpponentsInternal(opponents);
}
