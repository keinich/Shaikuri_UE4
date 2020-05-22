// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractionService.h"

// Game Includes
#include "GBGameStateBase.h"

#pragma region " Engine Callbacks "

// Sets default values
AInteractionService::AInteractionService() {
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractionService::BeginPlay() {
  Super::BeginPlay();

}

// Called every frame
void AInteractionService::Tick(float DeltaTime) {
  Super::Tick(DeltaTime);

}

#pragma endregion

void AInteractionService::PresentInteractionText(const FText& text, UObject* worldContextObject) {
  AGBGameStateBase::GetInteractionService(worldContextObject)->PresentInteractionTextInternal(text);
}

void AInteractionService::StopPresentInteractionText(UObject* worldContextObject) {
  AGBGameStateBase::GetInteractionService(worldContextObject)->StopPresentInteractionTextInternal();
}



