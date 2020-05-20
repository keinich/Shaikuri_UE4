// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "AIController.h"

// Game Inculdes
#include "Battle/AiFighterComponent.h"

// Last Include
#include "GemBinderAIController.generated.h"

/**
 *
 */
UCLASS()
class SHAIKURI_API AGemBinderAIController : public AAIController {
  GENERATED_BODY()

#pragma region Engine Callbacks

public:
  AGemBinderAIController();

  UFUNCTION()
    void Tick(float delta) override;

#pragma endregion

#pragma region Components

public:

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Battle")
    UAiFighterComponent* FighterComponent;

#pragma endregion

public: // UFunctions

public: // UProperties

protected: // UFunctions

protected: // UProperties

protected: // Functions

protected: // Fields

private: // Functions

private: // Fields
};
