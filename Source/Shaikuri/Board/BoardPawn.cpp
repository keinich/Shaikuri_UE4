// Fill out your copyright notice in the Description page of Project Settings.


#include "BoardPawn.h"

#pragma region Engine Callbacks

ABoardPawn::ABoardPawn() {

  SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
  SpringArm->SetupAttachment(GetMeshComponent());  
  Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
  Camera->SetupAttachment(SpringArm);

}

void ABoardPawn::SetupPlayerInputComponent(UInputComponent* InInputComponent) {
  Super::SetupPlayerInputComponent(InInputComponent);

}

#pragma endregion