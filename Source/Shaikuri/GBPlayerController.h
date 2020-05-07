// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GBPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHAIKURI_API AGBPlayerController : public APlayerController
{
	GENERATED_BODY()
	
#pragma region Engine Callbacks

public:

  virtual void BeginPlay() override;

#pragma endregion

public: // UFunctions

  UFUNCTION(BlueprintCallable, category = "Board")
    void StartPlacingBeast();

  UFUNCTION(BlueprintCallable, category = "Board")
    void CancelPlacingBeast();

public: // UProperties

protected: // UFunctions

protected: // UProperties

protected: // Functions

protected: // Fields

private: // Functions

  void OnLeftClick();
  void OnRightClickStart();
  void OnRightClickEnd();
  void OnTurn(float axisValue);
  void OnLookUp(float axisValue);

  bool TryGetActorUnderMouse(OUT FHitResult& hitResult) const;
  bool TryGetLookDirection(FVector2D screenPosition, OUT FVector& lookDirection) const;
  bool TryGetActorInLookDirection(FVector lookDirection, OUT FHitResult& hitResult) const;

  void TryHoverCell();
  void HoverOverCell(class ABoard* board, FVector locationOfClick3D);
  void HandleClickOnBoard(class ABoard* board, FVector locationOfClick3D);

private: // Fields  

  bool _IsRotating;

  bool _IsPlacingBeast;

  UPROPERTY()
    class ABoard* _Board;
};
