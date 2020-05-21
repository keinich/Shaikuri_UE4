// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "Battle/FighterComponent.h"

// Game Includes

// Last Include
#include "AiFighterComponent.generated.h"

// Forward Declarations

/**
 *
 */
UCLASS()
class SHAIKURI_API UAiFighterComponent : public UFighterComponent {
  GENERATED_BODY()

#pragma region Engine Callbacks



#pragma endregion

#pragma region Components



#pragma endregion

public: // UFunctions  

  virtual void StartTurn() override;

public: // UProperties

protected: // UFunctions

protected: // UProperties

private: // Functions

private: // Fields

};
