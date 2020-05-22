// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldCharacter.h"

// Engine Includes

// Game Includes
#include "MorphableSkeletalMeshComponent.h"
#include "MeshTraitsComponent.h"
#include "Battle/BattleService.h"
#include "Interaction/InteractionService.h"

// Sets default values
AWorldCharacter::AWorldCharacter() {
  // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  // Set up Body
  Body = CreateDefaultSubobject<UMorphableSkeletalMeshComponent>(TEXT("Body"));
  Body->SetupAttachment(GetMesh());

  // Set up Mesh Traits
  MeshTraits = CreateDefaultSubobject<UMeshTraitsComponent>(TEXT("MeshTraits"));

}

void AWorldCharacter::OnStartPlacingGem(FGemDefinition gemDefinition) {
  IsPlacingGem = true;
}

void AWorldCharacter::OnInteract_Implementation(AActor* caller) {
  TArray<AController*> controllers;
  controllers.Add(GetController());
  AInteractionService::StopPresentInteractionText(this);
  ABattleService::StartBattlePlayerAgainstControllers(controllers, this);
}

void AWorldCharacter::StartFocus_Implementation(AActor* caller) {
  AInteractionService::PresentInteractionText(FText::FromString("Start Fight"), this);
}

void AWorldCharacter::EndFocus_Implementation(AActor* caller) {
  AInteractionService::StopPresentInteractionText(this);
}

// Called when the game starts or when spawned
void AWorldCharacter::BeginPlay() {
  Super::BeginPlay();

}

// Called every frame
void AWorldCharacter::Tick(float DeltaTime) {
  Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWorldCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
  Super::SetupPlayerInputComponent(PlayerInputComponent);

}

