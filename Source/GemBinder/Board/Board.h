// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includs
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"

// Game Includes

// LAST Include
#include "Board.generated.h"

// Forward Declarations
class UBoardCellComponent;

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

  FVector2D GetCellCoordinatesFromLocation3D(FVector location3D);

  void SelectCell(int x, int y);
  FTransform GetCellTransform(int x, int y);
  void HoverCell(int x, int y);
  void UnhoverAllCells();

  UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    UBoardCellComponent* GetBoardCell(int x, int y);

  UFUNCTION(BlueprintCallable)
    TArray<FVector2D> GetCellCoordinates();

public: // UProperties

protected: // UFunctions

  UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void ConstructGridcell(FTransform transform);

  UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    UBoardCellComponent* ConstructGridcell1(FTransform transform);

  UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void SetCellSelectedMesh(class UBoardCellComponent* boardCellComponent);

  UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void SetCellHoveredMesh(class UBoardCellComponent* boardCellComponent);

  UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void SetCellUnselectedMesh(class UBoardCellComponent* boardCellComponent);

  UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void SetCellBasicMesh(class UBoardCellComponent* boardCellComponent);

  UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void SpawnBeast(FTransform spawnTransform);

protected: // UProperties  

  UPROPERTY(EditDefaultsOnly, Category = "Board")
    float InnerCellRadiusCm = 100.0f;

  UPROPERTY(EditDefaultsOnly, Category = "Board")
    int NumberCellsX = 5;

  UPROPERTY(EditDefaultsOnly, Category = "Board")
    int NumberCellsY = 5;

private: // Functions

  void RecreateGrid();

  bool TryGetCoordinates(FVector2D shiftedCenterWorldPositionXY, OUT FVector2D &coordinates);

private: // Fields

  UPROPERTY()
    float _OuterCellRadiusCm;

  UPROPERTY()
    FVector2D _SelectedCellCoordinates = FVector2D(-1,-1);

  UPROPERTY()
    FVector2D _HoveredCellCoordinates = FVector2D(-1, -1);

  TArray<FVector2D> _CellCoordinates;
};
