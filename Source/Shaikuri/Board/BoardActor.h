// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Last Include!!
#include "BoardActor.generated.h"

UCLASS()
class SHAIKURI_API ABoardActor : public APawn {
  GENERATED_BODY()

#pragma region Engine Callbacks

public:
  // Sets default values for this pawn's properties
  ABoardActor();

  // Called every frame
  virtual void Tick(float DeltaTime) override;

  // Called to bind functionality to input
  virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

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

protected: // Fields

private: // Functions

  void TurnCamera(float axisValue);
  void LookUp(float axisValue);

private: // Fields

};