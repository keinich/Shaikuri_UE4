// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"

#include "BoardCell.generated.h"

UCLASS()
class SHAIKURI_API ABoardCell : public AActor {
  GENERATED_BODY()

#pragma region Engine Callbacks

public:

  // Sets default values for this actor's properties
  ABoardCell();

  // Called every frame
  virtual void Tick(float DeltaTime) override;

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

#pragma endregion

public: // UFunctions

public: // UProperties

protected: // UFunctions

protected: // UProperties

  UPROPERTY(EditDefaultsOnly)
    UStaticMeshComponent* CellMesh;

protected: // Functions

protected: // Fields

private: // Functions

private: // Fields

};
