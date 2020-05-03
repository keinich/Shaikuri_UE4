// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includs
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"

// My Includes
#include "BoardCell.h"

// LAST Include
#include "Board.generated.h"

UCLASS()
class SHAIKURI_API ABoard : public AActor {
  GENERATED_BODY()

#pragma region Engine Callbacks

public: // Functions
// Sets default values for this actor's properties
  ABoard();

  // Called every frame
  virtual void Tick(float DeltaTime) override;

protected:

  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  virtual void OnConstruction(const FTransform& Transform) override;

#pragma endregion

#pragma region Components

public:

#pragma endregion

public: // UFunctions

public: // UProperties

protected: // UFunctions

  UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void ConstructGridcell(FTransform transform);

protected: // UProperties  

  UPROPERTY(EditDefaultsOnly, Category = "Board")
    float InnerCellRadiusCm = 100.0f;

  UPROPERTY(EditDefaultsOnly, Category = "Board")
    int NumberCellsX = 5;

  UPROPERTY(EditDefaultsOnly, Category = "Board")
    int NumberCellsY = 5;

protected: // Functions

protected: // Fields

private: // Functions

  void RecreateGrid();

private: // Fields

};
