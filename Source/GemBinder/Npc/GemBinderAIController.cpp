// Fill out your copyright notice in the Description page of Project Settings.


#include "GemBinderAIController.h"

#pragma region Engine Callbacks

AGemBinderAIController::AGemBinderAIController() {

  FighterComponent = CreateDefaultSubobject<UAiFighterComponent>(FName("Fighter Component"));

}

#pragma endregion

void AGemBinderAIController::Tick(float delta) {
  APawn* pawn = GetPawn();
  if (!pawn) {
    return;
  }
  pawn->AddActorLocalRotation(FRotator(1.0f, 0.0f, 0.0f));
}
