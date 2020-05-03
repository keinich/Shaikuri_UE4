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

protected:

  virtual void BeginPlay() override;

#pragma endregion

  // public: UFunctions

public: // UProperties

protected: // UFunctions

protected: // UProperties

protected: // Functions

protected: // Fields

private: // Functions

private: // Fields

};
