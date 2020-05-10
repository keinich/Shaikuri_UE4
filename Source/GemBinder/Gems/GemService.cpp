// Fill out your copyright notice in the Description page of Project Settings.

#include "GemService.h"

// Engine Includes

// Game Includes
#include "GBGameStateBase.h"

#pragma region Engine Callbacks

// Sets default values
AGemService::AGemService() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGemService::BeginPlay() {
	Super::BeginPlay();

}

// Called every frame
void AGemService::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

#pragma endregion

AGem* AGemService::SpawnGem(FTransform transform, UObject* worldContextObject) {
	return AGBGameStateBase::GetGemService(worldContextObject)->SpawnGemInternal(transform);
}



