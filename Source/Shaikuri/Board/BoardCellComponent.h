// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "BoardCellComponent.generated.h"

/**
 *
 */
UCLASS()
class SHAIKURI_API UBoardCellComponent : public UStaticMeshComponent {
  GENERATED_BODY()

#pragma region Engine Callbacks



#pragma endregion

#pragma region Components



#pragma endregion

public: // UFunctions

public: // UProperties

  UPROPERTY(BlueprintReadonly, category = "Board")
    FVector2D Coordinates;

protected: // UFunctions

protected: // UProperties

protected: // Functions

protected: // Fields

private: // Functions

private: // Fields

};
