// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

  // Engine Includes
#include "CoreMinimal.h"
#include "Battle/FighterComponent.h"

// Game Includes

// Last Include
#include "PlayerFighterComponent.generated.h"

// Forward Declarations

/**
 *
 */
UCLASS()
class SHAIKURI_API UPlayerFighterComponent : public UFighterComponent {
  GENERATED_BODY()

#pragma region Engine Callbacks



#pragma endregion

#pragma region Components



#pragma endregion

public: // UFunctions
    
    virtual void DrawStartingHand() override;

public: // UProperties

protected: // UFunctions

protected: // UProperties

protected: // Functions

protected: // Fields

private: // Functions

private: // Fields
};
