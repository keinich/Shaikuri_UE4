// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

// Game Includes

// Last Include
#include "GBGameStateBase.generated.h"

/**
 *
 */
UCLASS()
class SHAIKURI_API AGBGameStateBase : public AGameStateBase {
  GENERATED_BODY()

#pragma region Engine Callbacks

public:

  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

#pragma endregion

#pragma region Components



#pragma endregion

public: // UFunctions

public: // UProperties

protected: // UFunctions

  UFUNCTION(BlueprintImplementableEvent)
    void InitServices();

protected: // UProperties

  UPROPERTY(BlueprintReadWrite)
    class ABattleService* BattleService;

protected: // Functions

protected: // Fields

private: // Functions

private: // Fields  

};
