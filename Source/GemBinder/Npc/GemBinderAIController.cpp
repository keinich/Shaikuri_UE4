// Fill out your copyright notice in the Description page of Project Settings.


#include "GemBinderAIController.h"

#pragma region Engine Callbacks

AGemBinderAIController::AGemBinderAIController() {

  FighterComponent = CreateDefaultSubobject<UAiFighterComponent>(FName("Fighter Component"));

}

void AGemBinderAIController::OnPossess(APawn* InPawn) {
  Super::OnPossess(InPawn);

  FighterComponent->TrySetWorldCharacter(InPawn);  
}

#pragma endregion

void AGemBinderAIController::Tick(float delta) {
  APawn* pawn = GetPawn();
  if (!pawn) {
    return;
  }
}
