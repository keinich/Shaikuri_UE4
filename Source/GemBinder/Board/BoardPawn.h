// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Last Include
#include "BoardPawn.generated.h"

/**
 *
 */
UCLASS()
class SHAIKURI_API ABoardPawn : public ADefaultPawn {
  GENERATED_BODY()

#pragma region Engine Callbacks

public:

  ABoardPawn();

protected:

    virtual void SetupPlayerInputComponent(UInputComponent* InInputComponent) override;

#pragma endregion

#pragma region Components

    UPROPERTY(EditDefaultsOnly, category = "Camera")
    USpringArmComponent* SpringArm;

  UPROPERTY(EditDefaultsOnly, category = "Camera")
    UCameraComponent* Camera;

#pragma endregion

public: // UFunctions

public: // UProperties

protected: // UFunctions

protected: // UProperties

protected: // Functions

  UPROPERTY(EditDefaultsOnly, category = "Camera")
    float ZoomSpeed = 100.0f;

protected: // Fields

private: // Functions

  void ZoomIn(float axisValue);
  void OnRightClickStart();
  void OnRightClickEnd();
  void OnTurn(float axisValue);
  void OnLookUp(float axisValue);

private: // Fields

  bool _IsRotating;

};
