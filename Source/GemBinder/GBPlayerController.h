// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

// Game Includes
#include "Battle/PlayerFighterComponent.h"

// Last Include
#include "GBPlayerController.generated.h"

/**
 *
 */
UCLASS()
class SHAIKURI_API AGBPlayerController : public APlayerController {
  GENERATED_BODY()

#pragma region Engine Callbacks

public:

  AGBPlayerController();

  virtual void BeginPlay() override;

protected:

  virtual void OnPossess(APawn* InPawn) override;

#pragma endregion

#pragma region Components

public:

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Battle")
    UPlayerFighterComponent* FighterComponent;

#pragma endregion

public: // UFunctions

  UFUNCTION()
    bool TryGetActorUnderMouse(FHitResult& hitResult) const;

public: // UProperties

protected: // UFunctions

protected: // UProperties

protected: // Functions

protected: // Fields

private: // Functions 

  bool TryGetLookDirection(FVector2D screenPosition, FVector& lookDirection) const;
  bool TryGetActorInLookDirection(FVector lookDirection, FHitResult& hitResult) const;

private: // Fields  

};
