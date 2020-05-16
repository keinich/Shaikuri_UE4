// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"

// Game Includes
#include "Board/Board.h"

// Last Include
#include "BattleService.generated.h"

// Forward Declarations

class UFighterComponent;
class ABattle;

UCLASS()
class SHAIKURI_API ABattleService : public AActor {
  GENERATED_BODY()

#pragma region Engine Callbacks

public:
  // Sets default values for this actor's properties
  ABattleService();

  // Called every frame
  virtual void Tick(float DeltaTime) override;

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

#pragma endregion

#pragma region Components



#pragma endregion

public: // UFunctions

  UFUNCTION(BlueprintCallable, category = "Battle")
    static void StartBattle(
      TArray<UFighterComponent*> fighters,
      FTransform transform, 
      const UObject* worldContextObject
  );

  UFUNCTION(BlueprintCallable, category = "Battle")
    static void StartBattlePlayerAgainstOpponents(TArray<UFighterComponent*> opponents, const UObject* worldContextObject);
  
public: // UProperties

protected: // UFunctions

  UFUNCTION(BlueprintImplementableEvent, category = "Battle")
    UUserWidget* CreateBattleHud(UPlayerFighterComponent* playerFighterComponent);

protected: // Properties

  UPROPERTY(EditDefaultsOnly, category = "Battle")
  TSubclassOf<ABattle> BattleClass;

  UPROPERTY(EditDefaultsOnly, category = "Battle")
  TSubclassOf<ABoardPawn> BoardPawnClass;

  UPROPERTY(EditDefaultsOnly, category = "Battle")
    TSubclassOf<ABoard> BoardClass;

private: // Functions

  UFUNCTION(BlueprintCallable, category = "Battle")
    ABattle* CreateBattle();

  UFUNCTION(BlueprintCallable, category = "Battle")
    class ABoardPawn* SpawnBoardPawn(FTransform transform);

  UFUNCTION(BlueprintCallable, category = "Battle")
    class ABoard* SpawnBoard(FTransform transform);

  UFUNCTION(BlueprintCallable, category = "Battle")
    void StartBattleInternal(TArray<UFighterComponent*> fighters, FTransform transform);

  UFUNCTION(BlueprintCallable, category = "Battle")
    void StartBattlePlayerAgainsOpponentsInternal(TArray<UFighterComponent*> opponents);

private: // Fields

};
