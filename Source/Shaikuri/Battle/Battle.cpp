// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle.h"

#pragma region Engine Callbacks

// Sets default values
ABattle::ABattle() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABattle::BeginPlay() {
	Super::BeginPlay();

}

// Called every frame
void ABattle::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

#pragma endregion

void ABattle::Start(TArray<UFighterComponent*> fighters) {
	//_Fighters = fighters;
	//SetGameMode();
	ShowUi();
}

