// Fill out your copyright notice in the Description page of Project Settings.

#include "BoardPawn.h"

// Engine Includes

#include "Components/InputComponent.h"

#pragma region Engine Callbacks

ABoardPawn::ABoardPawn() {

  SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
  SpringArm->SetupAttachment(RootComponent);  
  Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
  Camera->SetupAttachment(SpringArm);

}

void ABoardPawn::SetupPlayerInputComponent(UInputComponent* InInputComponent) {
  Super::SetupPlayerInputComponent(InInputComponent);

  InInputComponent->BindAxis("ZoomIn", this, &ABoardPawn::ZoomIn);

}

void ABoardPawn::ZoomIn(float axisValue) {
  SpringArm->TargetArmLength -= ZoomSpeed * axisValue;
}

#pragma endregion
