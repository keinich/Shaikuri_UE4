// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"

// Game Includes

// Last Include
#include "BattleService.generated.h"

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
    static void StartBattle(const UObject* worldContextObject);

public: // UProperties

protected: // UFunctions

  UFUNCTION(BlueprintImplementableEvent, category = "Battle")
    UUserWidget* CreateBattleHud();

protected: // UProperties

protected: // Functions

  UFUNCTION(BlueprintImplementableEvent, category = "Battle")
    class ABoardPawn* SpawnBoardPawn(FTransform transform);

  UFUNCTION(BlueprintCallable, category = "Battle")
    void StartBattleInternal();

protected: // Fields

private: // Functions

private: // Fields

};
