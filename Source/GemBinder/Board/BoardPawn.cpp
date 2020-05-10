// Fill out your copyright notice in the Description page of Project Settings.

#include "BoardPawn.h"

// Engine Includes
#include "Components/InputComponent.h"

// Game Includes
#include "GBPlayerController.h"

#pragma region Engine Callbacks

ABoardPawn::ABoardPawn() {

  SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
  SpringArm->SetupAttachment(RootComponent);
  Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
  Camera->SetupAttachment(SpringArm);

}

void ABoardPawn::SetupPlayerInputComponent(UInputComponent* InInputComponent) {
  Super::SetupPlayerInputComponent(InInputComponent);

  AGBPlayerController* gbPlayerController = (AGBPlayerController*)(this->GetController());

  InInputComponent->BindAction("LeftClick", EInputEvent::IE_Released, gbPlayerController, &AGBPlayerController::OnLeftClick);
  InInputComponent->BindAction("CancelPlacing", EInputEvent::IE_Pressed, gbPlayerController, &AGBPlayerController::CancelPlacingBeast);
  InInputComponent->BindAxis("LookUp", gbPlayerController, &AGBPlayerController::OnHoverMouse);
  InInputComponent->BindAxis("Turn", gbPlayerController, &AGBPlayerController::OnHoverMouse);

  InInputComponent->BindAxis("LookUp", this, &ABoardPawn::OnLookUp);
  InInputComponent->BindAxis("Turn", this, &ABoardPawn::OnTurn);
  InInputComponent->BindAxis("ZoomIn", this, &ABoardPawn::ZoomIn);
  InInputComponent->BindAction("RightClick", EInputEvent::IE_Pressed, this, &ABoardPawn::OnRightClickStart);
  InInputComponent->BindAction("RightClick", EInputEvent::IE_Released, this, &ABoardPawn::OnRightClickEnd);

}

#pragma endregion

void ABoardPawn::ZoomIn(float axisValue) {
  SpringArm->TargetArmLength -= ZoomSpeed * axisValue; 
}

void ABoardPawn::OnRightClickStart() {
  _IsRotating = true;
}

void ABoardPawn::OnRightClickEnd() {
  _IsRotating = false;
}

void ABoardPawn::OnLookUp(float axisValue) {
  if (_IsRotating) {
    AddControllerPitchInput(axisValue);
  }
}

void ABoardPawn::OnTurn(float axisValue) {
  if (_IsRotating) {
    AddControllerYawInput(axisValue);
  }
}


void ABoardPawn::PlaceGemInHand(AGem* gem) {
  //gem->SetActorTransform(GetTransform());
  _Gem = gem;
  //gem->AttachToComponent(Hand, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}