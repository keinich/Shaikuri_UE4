// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

  // Engine Includes
#include "CoreMinimal.h"
#include "Battle/FighterComponent.h"

// Game Includes
#include "Gems/Gem.h"

// Last Include
#include "PlayerFighterComponent.generated.h"

// Forward Declarations

// Delegate Declarations
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGemDrawn, FGemDefinition, gemDefinition);

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

  UFUNCTION(BlueprintCallable, category = "Gem")
    void StartPlacingGem(FGemDefinition gemDefinition);

public: // UProperties

  UPROPERTY(BlueprintAssignable, category = "Gem")
    FOnGemDrawn OnGemDrawn;
  
protected: // UFunctions

  virtual void AfterGemDrawn(FGemDefinition gemDefinition) override;

protected: // UProperties

private: // Functions

private: // Fields

  bool _IsPlacingGem;

  UPROPERTY()
    FGemDefinition _GemToPlace;
};
