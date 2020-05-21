// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WorldCharacter.generated.h"

UCLASS()
class SHAIKURI_API AWorldCharacter : public ACharacter {
  GENERATED_BODY()

public: // Functions
  // Sets default values for this character's properties
  AWorldCharacter();

  // Called every frame
  virtual void Tick(float DeltaTime) override;

  // Called to bind functionality to input
  virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public: // Fields
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Look", meta = (AllowPrivateAccess = "true"))
    class UMorphableSkeletalMeshComponent* Body;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Traits", meta = (AllowPrivateAccess = "true"))
    class UMeshTraitsComponent* MeshTraits;

protected: // Functions
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

protected: // Fields

  UPROPERTY(BlueprintReadWrite, category = "Battle")
    bool IsPlacingGem;

};
