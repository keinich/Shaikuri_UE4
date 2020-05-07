// Fill out your copyright notice in the Description page of Project Settings.

#include "GBGameStateBase.h"

#pragma region Engine Callbacks

void AGBGameStateBase::BeginPlay() {
  InitServices();
}

#pragma endregion