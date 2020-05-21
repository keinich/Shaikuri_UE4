// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

  // Engine Includes
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

// Game Includes
#include "WorldCharacter.h"
#include "Gems/GemDefinition.h"

// Last Include
#include "FighterComponent.generated.h"

// Forward Declarations
class ABattle;

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
    void TrySetWorldCharacter(APawn* InPawn);

  UFUNCTION()
    virtual void StartBattle(ABattle* battle);

  UFUNCTION()
    virtual void DrawStartingHand();

  UFUNCTION()
    virtual void StartTurn();

  UFUNCTION()
    virtual void EndTurn();

public: // Properties

  UPROPERTY(EditAnywhere)
    FString Test;

protected: // Functions

  UFUNCTION()
    void StartSubmitPlacingGem(FGemDefinition gemDefinition);

  UFUNCTION()
    void DrawNextGem();

  UFUNCTION()
    virtual void AfterGemDrawn(FGemDefinition gemDefinition);

protected: // Properties

  UPROPERTY(EditDefaultsOnly, category = "Gem")
    TArray<FGemDefinition> Bag;

  UPROPERTY(EditDefaultsOnly, category = "Gem")
    TArray<FGemDefinition> Hand;

  UPROPERTY()
    ABattle* _Battle;
    
  UPROPERTY(VisibleAnywhere)
    class AWorldCharacter* OwningWorldCharacter;

    bool _HasTurn;

private: // Functions

private: // Fields
};
