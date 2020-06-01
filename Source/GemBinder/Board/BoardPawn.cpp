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

  CamTransitionTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Camera Transition Timeline"));

  InterpFunction.BindUFunction(this, FName("TimelineFloatReturn"));
  TimelineFinished.BindUFunction(this, FName("OnTimelineFinished"));

}

void ABoardPawn::SetupPlayerInputComponent(UInputComponent* InInputComponent) {
  Super::SetupPlayerInputComponent(InInputComponent);

  AGBPlayerController* gbPlayerController = (AGBPlayerController*)(this->GetController());
  UPlayerFighterComponent* fighterComponent = gbPlayerController->FighterComponent;

  // Interacting with the Battle
  InInputComponent->BindAction("LeftClick", EInputEvent::IE_Released, fighterComponent, &UPlayerFighterComponent::OnLeftClick);
  InInputComponent->BindAction("CancelPlacing", EInputEvent::IE_Pressed, fighterComponent, &UPlayerFighterComponent::CancelPlacingBeast);
  InInputComponent->BindAxis("LookUp", fighterComponent, &UPlayerFighterComponent::OnHoverMouse);
  InInputComponent->BindAxis("Turn", fighterComponent, &UPlayerFighterComponent::OnHoverMouse);

  // 3D Navigation
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

void ABoardPawn::TimelineFloatReturn(float value) {

  if (value < 0) {
    return;
  }
  if (value > 1) {
    return;
  }
  FVector relativeLocation = FMath::Lerp(_CurrentInitialRelativeCamTransform.GetLocation(), FVector(), value);
  FQuat relativeRotation = FMath::Lerp(
    _CurrentInitialRelativeCamTransform.GetRotation(),
    _CurrentTargetRelativeRotation,
    value
  );

  FTransform relativeTransform = FTransform();
  relativeTransform.SetLocation(relativeLocation);
  relativeTransform.SetRotation(relativeRotation);
  Camera->SetRelativeTransform(relativeTransform);
  //Camera->SetWorldLocation(FMath::Lerp(_CurrentInitialCamTransform.GetLocation(), FVector(0, 0, 0), value));
}

void ABoardPawn::OnTimelineFinished() {
  CamTransitionFinished.Broadcast();
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

void ABoardPawn::TransitionCameraFrom(FTransform initialTransform) {

  _CurrentTargetRelativeRotation = Camera->GetRelativeRotation().Quaternion();

  Camera->SetWorldTransform(initialTransform);

  _CurrentInitialCamTransform = initialTransform;
  _CurrentInitialRelativeCamTransform = Camera->GetRelativeTransform();

  if (CamTransitionCurve) {
    CamTransitionTimeline->AddInterpFloat(CamTransitionCurve, InterpFunction, FName("Alpha"));
    CamTransitionTimeline->SetTimelineFinishedFunc(TimelineFinished);

    CamTransitionTimeline->SetLooping(false);
    CamTransitionTimeline->SetIgnoreTimeDilation(true);

    CamTransitionTimeline->Play();
  }
}
