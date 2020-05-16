// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"

// Game Includes

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
    static void StartBattle(TArray<UFighterComponent*> fighters, const UObject* worldContextObject);

  UFUNCTION(BlueprintCallable, category = "Battle")
    static void StartBattlePlayerAgainstOpponents(TArray<UFighterComponent*> opponents, const UObject* worldContextObject);
  
public: // UProperties

protected: // UFunctions

  UFUNCTION(BlueprintImplementableEvent, category = "Battle")
    UUserWidget* CreateBattleHud(UPlayerFighterComponent* playerFighterComponent);

  UFUNCTION(BlueprintImplementableEvent, category = "Battle")
    class ABoardPawn* SpawnBoardPawn(FTransform transform);

protected: // Properties

  UPROPERTY(EditDefaultsOnly, category = "Battle")
  TSubclassOf<ABattle> BattleClass;

  UPROPERTY(EditDefaultsOnly, category = "Battle")
  TSubclassOf<ABoardPawn> BoardPawnClass;

private: // Functions

  UFUNCTION(BlueprintCallable, category = "Battle")
    ABattle* CreateBattle();

  UFUNCTION(BlueprintCallable, category = "Battle")
    void StartBattleInternal(TArray<UFighterComponent*> fighters);

  UFUNCTION(BlueprintCallable, category = "Battle")
    void StartBattlePlayerAgainsOpponentsInternal(TArray<UFighterComponent*> opponents);

private: // Fields

};
