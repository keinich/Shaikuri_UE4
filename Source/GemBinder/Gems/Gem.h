// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
// Engine Includes
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"

// Game Includes

// Last Include

// Forward Declarations

#include "Gem.generated.h"

UCLASS()
class SHAIKURI_API AGem : public AActor {
  GENERATED_BODY()

#pragma region Engine Callbacks

public:
  // Sets default values for this actor's properties
  AGem();

  // Called every frame
  virtual void Tick(float DeltaTime) override;

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

#pragma endregion

#pragma region Components

public:

  UPROPERTY(EditDefaultsOnly)
    UCapsuleComponent* Capsule;

  UPROPERTY(EditDefaultsOnly)
    UStaticMeshComponent* Mesh;

  UPROPERTY(EditDefaultsOnly, category = "Gem")
    UWidgetComponent* GemNameWidget;

  UPROPERTY(EditDefaultsOnly, category = "Gem")
    UWidgetComponent* GemImageWidget;

  UPROPERTY(EditDefaultsOnly, category = "Gem")
    UWidgetComponent* GemDescriptionWidget;

#pragma endregion

public: // UFunctions

public: // UProperties

protected: // UFunctions

protected: // UProperties

protected: // Functions

protected: // Fields

private: // Functions

private: // Fields

};
