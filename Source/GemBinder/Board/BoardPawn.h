// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ChildActorComponent.h"
#include "Components/TimelineComponent.h"

// Last Include
#include "BoardPawn.generated.h"

// Forward Declarations
//class AGem

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

  UPROPERTY(EditDefaultsOnly, Category = "Camera Transition")
    UTimelineComponent* CamTransitionTimeline;

#pragma endregion

public: // UFunctions

  UFUNCTION()
    void PlaceGemInHand(AGem* gem);

  UFUNCTION()
    void TransitionCameraFrom(FTransform initialTransform);

public: // UProperties

protected: // Functions

  UPROPERTY(EditDefaultsOnly, category = "Camera")
    float ZoomSpeed = 100.0f;

protected: // Properties

  UPROPERTY(EditAnywhere, Category = "Camera Transition")
    class UCurveFloat* CamTransitionCurve;

private: // Functions

  void ZoomIn(float axisValue);
  void OnRightClickStart();
  void OnRightClickEnd();
  void OnTurn(float axisValue);
  void OnLookUp(float axisValue);

  UFUNCTION()
    void TimelineFloatReturn(float value);

  UFUNCTION()
    void OnTimelineFinished();

private: // Fields

  bool _IsRotating;

  UPROPERTY()
    AGem* _Gem;
    
  FOnTimelineFloat InterpFunction;
  //TODO wtf are the brackets?
  FOnTimelineEvent TimelineFinished{};

  FTransform _CurrentInitialCamTransform;
  FTransform _CurrentInitialRelativeCamTransform;
  FQuat _CurrentTargetRelativeRotation;
};
