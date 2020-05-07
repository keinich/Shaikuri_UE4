// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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
    void StartBattle();

public: // UProperties

protected: // UFunctions

protected: // UProperties

protected: // Functions

  UFUNCTION(BlueprintImplementableEvent, category = "Battle")
    class ABoardPawn* SpawnBoardPawn(FTransform transform);

protected: // Fields

private: // Functions

private: // Fields
};
