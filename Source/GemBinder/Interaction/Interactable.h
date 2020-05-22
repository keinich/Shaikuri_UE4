// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

  // Engine Includes
#include "CoreMinimal.h"
#include "UObject/Interface.h"

// Game Includes

// Last Include
#include "Interactable.generated.h"

// Forward Declarations


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface {
  GENERATED_BODY()
};

class SHAIKURI_API IInteractable {
  GENERATED_BODY()

public: // UFunctions

  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
    void OnInteract(AActor* caller);

  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
    void StartFocus(AActor* caller);

  UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
    void EndFocus(AActor* caller);

};
