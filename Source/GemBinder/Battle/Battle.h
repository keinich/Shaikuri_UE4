// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// Game Includes
#include "Gems/GemDefinition.h"

// Last Include
#include "Battle.generated.h"

// Forward Declarations
class UFighterComponent;
class ABoard;

UCLASS()
class SHAIKURI_API ABattle : public AActor {
  GENERATED_BODY()

#pragma region Engine Callbacks

public:
  // Sets default values for this actor's properties
  ABattle();

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
    void Start(TArray<UFighterComponent*> fighters, ABoard* board);

  UFUNCTION(BlueprintCallable, category = "Battle")
    void PlaceGem(ABoard* board, FVector2D coordinates, FGemDefinition gemDefinition);

  UFUNCTION(BlueprintCallable, category = "Battle")
    void SubmitTurn(UFighterComponent* fighter);

public: // UProperties

protected: // UFunctions

protected: // UProperties

protected: // Functions

protected: // Fields

private: // Functions

  void PassTurnToNextPlayer();

private: // Fields

  UPROPERTY()
    TArray<UFighterComponent*> _Fighters;

  UPROPERTY()
    ABoard* _Board;

  UPROPERTY()
    UFighterComponent* _FighterWhoHasTurn;
};
