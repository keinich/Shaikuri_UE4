// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"

// Game Includes
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Last Include
#include "GrabberComponent.generated.h"

// Forward Declarations


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHAIKURI_API UGrabberComponent : public UActorComponent {
  GENERATED_BODY() 

#pragma region Engine Callbacks

public:
  // Sets default values for this component's properties
  UGrabberComponent();

  // Called every frame
  virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
  // Called when the game starts
  virtual void BeginPlay() override;

#pragma endregion

#pragma region Components





#pragma endregion

public: // UFunctions

public: // UProperties

protected: // UFunctions

protected: // UProperties

private: // Functions

  void Release();

  // Ray-cast and grab what's in reach
  void Grab();

  //Find attached PhysicsComponent
  void FindPhysicsHandleComponent();

  // Setup (assumed) attached input component
  void SetUpInputComponent();

  // Return hit for first physics body in reach
  const FHitResult GetFirstPhysicsBodyInReach();

  // Get Endpoint of the Reachline
  FVector GetReachLineEnd();

  // Get Endpoint of the Reachline
  FVector GetReachLineStart();

private: // Fields

  float Reach = 100.f;

  UPhysicsHandleComponent* PhysicsHandle = nullptr;

  UInputComponent* InputComponent = nullptr;

};
