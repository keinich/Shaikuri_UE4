// Fill out your copyright notice in the Description page of Project Settings.


#include "GBGameModeBase.h"

void AGBGameModeBase::SetHud(UUserWidget* hudToSet) {

  if (CurrentHud) {
    CurrentHud->RemoveFromViewport();
  }

  CurrentHud = hudToSet;

  if (CurrentHud) {
    CurrentHud->AddToViewport();
  }

}
