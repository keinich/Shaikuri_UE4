// Fill out your copyright notice in the Description page of Project Settings.


#include "GemBinderAIController.h"

#pragma region Engine Callbacks

AGemBinderAIController::AGemBinderAIController() {

  FighterComponent = CreateDefaultSubobject<UAiFighterComponent>(FName("Fighter Component"));

}

#pragma endregion