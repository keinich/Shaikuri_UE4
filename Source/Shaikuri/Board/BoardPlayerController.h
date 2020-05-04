// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BoardPlayerController.generated.h"

/**
 *
 */
UCLASS()
class SHAIKURI_API ABoardPlayerController : public APlayerController {
  GENERATED_BODY()

#pragma region Engine Callbacks

public:

  virtual void BeginPlay() override;

#pragma endregion

public: // UFunctions

public: // UProperties

protected: // UFunctions

protected: // UProperties

protected: // Functions

protected: // Fields

private: // Functions

  void OnLeftClick();

  bool TryGetLookDirection(FVector2D screenPosition, OUT FVector& lookDirection) const;

  bool TryGetClickedActor(FVector lookDirection, OUT TWeakObjectPtr<AActor> &hitActor) const;

private: // Fields  

};
