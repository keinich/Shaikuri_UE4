// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

  // Engine Includes
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

// Game Includes
#include "Gems/GemDefinition.h"

// Last Include
#include "FighterComponent.generated.h"

// Forward Declarations


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHAIKURI_API UFighterComponent : public UActorComponent {
  GENERATED_BODY()

#pragma region Engine Callbacks

public:
  // Sets default values for this component's properties
  UFighterComponent();


  // Called every frame
  virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
  // Called when the game starts
  virtual void BeginPlay() override;

#pragma endregion

#pragma region Components



#pragma endregion

public: // UFunctions

  UFUNCTION()
    virtual void DrawStartingHand();

public: // UProperties

  UPROPERTY(EditAnywhere)
    FString Test;

protected: // UFunctions

  UFUNCTION()
    void DrawNextGem();

  UFUNCTION()
    virtual void OnGemDrawn();

protected: // UProperties

  UPROPERTY(EditDefaultsOnly, category = "Gem")
    TArray<FGemDefinition> Bag;

protected: // Functions

protected: // Fields

private: // Functions

private: // Fields

  UPROPERTY(EditDefaultsOnly, category = "Gem")
    TArray<FGemDefinition> _Hand;

};
