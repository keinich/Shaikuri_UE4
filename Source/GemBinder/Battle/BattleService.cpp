// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleService.h"

// Engine Includes
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "GameFramework/GameState.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/PlayerCameraManager.h"
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

ABattle* ABattleService::CreateBattle() {
  FActorSpawnParameters spawnParameters;
  ABattle* battle = GetWorld()->SpawnActor<ABattle>(BattleClass, spawnParameters);
  return battle;
}

ABoardPawn* ABattleService::SpawnBoardPawn(FTransform transform) {
  FActorSpawnParameters spawnParams;
  spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
  return GetWorld()->SpawnActor<ABoardPawn>(BoardPawnClass, transform, spawnParams);
}

ABoard* ABattleService::SpawnBoard(FTransform transform) {
  FActorSpawnParameters spawnParams;
  spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
  return GetWorld()->SpawnActor<ABoard>(BoardClass, transform, spawnParams);
}

void ABattleService::StartBattleInternal(TArray<UFighterComponent*> fighters, FTransform transform) {

  // Spawn Board
  ABoard* board = SpawnBoard(transform);

  // Instantiate Battle
  ABattle* battle = CreateBattle();
  battle->Start(fighters, board);

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
  FTransform transformPawn = transform;

  UCameraComponent* cam = (UCameraComponent*)pawn->GetComponentByClass(UCameraComponent::StaticClass());
  FTransform camTransform = cam->GetComponentTransform();

  transformPawn.AddToTranslation(FVector(0, 0, 100.0f));
  ABoardPawn* boardPawn = SpawnBoardPawn(transformPawn);
  boardPawn->TransitionCameraFrom(camTransform);
  playerController->UnPossess();
  playerController->Possess(boardPawn);
  boardPawn->CamTransitionFinished.AddLambda([opponents, transform, this]() {
    StartBattleInternal(opponents, transform);
  });

}

void ABattleService::StartBattlePlayerAgainsControllersInternal(TArray<AController*> opponents) {

  TArray<UFighterComponent*> fighterComponents;

  for (int i = 0; i < opponents.Num(); ++i) {
    UFighterComponent* fighterComponent = (UFighterComponent*)opponents[i]->GetComponentByClass(UFighterComponent::StaticClass());
    fighterComponents.Add(fighterComponent);
  }

  StartBattlePlayerAgainsOpponentsInternal(fighterComponents);
}

void ABattleService::StartBattle(
  TArray<UFighterComponent*> fighters,
  FTransform transform,
  const UObject* worldContextObject) {
  return AGBGameStateBase::GetBattleService(worldContextObject)->StartBattleInternal(fighters, transform);
}

void ABattleService::StartBattlePlayerAgainstOpponents(
  TArray<UFighterComponent*> opponents, const UObject* worldContextObject
) {
  AGBGameStateBase::GetBattleService(worldContextObject)->StartBattlePlayerAgainsOpponentsInternal(opponents);
}

void ABattleService::StartBattlePlayerAgainstControllers(TArray<AController*> opponents, const UObject* worldContextObject) {
  AGBGameStateBase::GetBattleService(worldContextObject)->StartBattlePlayerAgainsControllersInternal(opponents);
}

void ABattleService::Test() {}
