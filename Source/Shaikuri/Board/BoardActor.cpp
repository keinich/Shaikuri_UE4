// Fill out your copyright notice in the Description page of Project Settings.

// Engine Includes
#include "Components/InputComponent.h"

#include "BoardActor.h"

#pragma region Engine Callbacks

// Sets default values
ABoardActor::ABoardActor() {
  // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
  SpringArm->SetupAttachment(RootComponent);
  Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
  Camera->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void ABoardActor::BeginPlay() {
  Super::BeginPlay();

}

// Called every frame
void ABoardActor::Tick(float DeltaTime) {
  Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABoardActor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
  Super::SetupPlayerInputComponent(PlayerInputComponent);

  PlayerInputComponent->BindAxis("Turn", this, &ABoardActor::TurnCamera);
  PlayerInputComponent->BindAxis("LookUp", this, &ABoardActor::LookUp);
}

#pragma endregion

void ABoardActor::TurnCamera(float axisValue) {
  AddControllerYawInput(axisValue);
}

void ABoardActor::LookUp(float axisValue) {
  AddControllerPitchInput(axisValue);
}