// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//TODO auf Toplevel verschieben

// Engine Includes
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"

// Last Include
#include "GBGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class SHAIKURI_API AGBGameModeBase : public AGameModeBase {
  GENERATED_BODY()

#pragma region Engine Callbacks



#pragma endregion

#pragma region Components



#pragma endregion

public: // UFunctions

  UFUNCTION(BlueprintCallable)
    void SetHud(UUserWidget* hudToSet);

public: // UProperties

protected: // UFunctions

protected: // UProperties

  UPROPERTY(BlueprintReadWrite)
    UUserWidget* CurrentHud;

protected: // Functions

protected: // Fields

private: // Functions

private: // Fields

};
