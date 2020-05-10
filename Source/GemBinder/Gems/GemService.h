// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

  // Engine Includes
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// Game Includes
#include "Gem.h"

// Last Include
#include "GemService.generated.h"

// Forward Declarations


UCLASS()
class SHAIKURI_API AGemService : public AActor {
  GENERATED_BODY()

#pragma region Engine Callbacks

public:
  // Sets default values for this actor's properties
  AGemService();

  // Called every frame
  virtual void Tick(float DeltaTime) override;

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

#pragma endregion

#pragma region Components



#pragma endregion

public: // UFunctions

  UFUNCTION(BlueprintCallable, category = "Gem")
    static AGem* SpawnGem(FTransform transform, UObject* worldContextObject);

public: // UProperties

protected: // UFunctions

  UFUNCTION(BlueprintImplementableEvent)
    AGem* SpawnGemInternal(FTransform transform);

protected: // UProperties

private: // Functions

private: // Fields

};
