// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

// Game Includes
#include "Battle/PlayerFighterComponent.h"

// Last Include
#include "GBPlayerController.generated.h"

UENUM()
enum EGemBinderPlayerControllerState {
  OpenWorld,
  Battle
};

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

  virtual void Tick(float deltaTime) override;

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

protected: // Functions

  UFUNCTION(BlueprintCallable)
    void TryInteract();

protected: // Properties

  UPROPERTY(EditDefaultsOnly)
    float TraceDistance;

private: // Functions 

  bool TryGetLookDirection(FVector2D screenPosition, FVector& lookDirection) const;
  bool TryGetActorInLookDirection(FVector lookDirection, FHitResult& hitResult) const;

  UFUNCTION()
    bool TryGetActorTracingForward(FHitResult& hitResult) const;

  void CheckForInteractables();

private: // Fields  

  EGemBinderPlayerControllerState _State;

  AActor* _CurrentInteractable;

};
