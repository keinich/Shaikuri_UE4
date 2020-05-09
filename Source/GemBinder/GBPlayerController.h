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

#pragma endregion

#pragma region Components

public:

  UPROPERTY(EditDefaultsOnly, category = "Battle")
    UPlayerFighterComponent* FighterComponent;

#pragma endregion

public: // UFunctions

  UFUNCTION(BlueprintCallable, category = "Board")
    void StartPlacingBeast();

  UFUNCTION(BlueprintCallable, category = "Board")
    void CancelPlacingBeast();

  void OnLeftClick();
  void OnHoverMouse(float axisValue);

public: // UProperties

protected: // UFunctions

protected: // UProperties

protected: // Functions

protected: // Fields

private: // Functions

  bool TryGetActorUnderMouse(OUT FHitResult& hitResult) const;
  bool TryGetLookDirection(FVector2D screenPosition, OUT FVector& lookDirection) const;
  bool TryGetActorInLookDirection(FVector lookDirection, OUT FHitResult& hitResult) const;

  void TryHoverCell();
  void HoverOverCell(class ABoard* board, FVector locationOfClick3D);
  void HandleClickOnBoard(class ABoard* board, FVector locationOfClick3D);

private: // Fields  

  bool _IsPlacingBeast;

  UPROPERTY()
    class ABoard* _Board;
};
