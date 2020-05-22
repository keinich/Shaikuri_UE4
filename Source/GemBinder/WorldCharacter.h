// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine Includes
#include "CoreMinimal.h"
#include "GameFramework/Character.h"

// Game Includes
#include "Gems/GemDefinition.h"
#include "Interaction/Interactable.h"

// Last Include
#include "WorldCharacter.generated.h"

UCLASS()
class SHAIKURI_API AWorldCharacter : public ACharacter, public IInteractable {
  GENERATED_BODY()

#pragma region Engine Callbacks

public: // Functions
  // Sets default values for this character's properties
  AWorldCharacter();

  // Called every frame
  virtual void Tick(float DeltaTime) override;

  // Called to bind functionality to input
  virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma endregion

#pragma region Components

public: // Fields

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Look", meta = (AllowPrivateAccess = "true"))
    class UMorphableSkeletalMeshComponent* Body;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Traits", meta = (AllowPrivateAccess = "true"))
    class UMeshTraitsComponent* MeshTraits;

#pragma endregion

public: // Functions

  void OnStartPlacingGem(FGemDefinition gemDefinition);

  void OnInteract_Implementation(AActor* caller) override;
  void StartFocus_Implementation(AActor* caller) override;
  void EndFocus_Implementation(AActor* caller) override;

protected: // Functions

  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

protected: // Fields

  UPROPERTY(BlueprintReadWrite, category = "Battle")
    bool IsPlacingGem;

};
