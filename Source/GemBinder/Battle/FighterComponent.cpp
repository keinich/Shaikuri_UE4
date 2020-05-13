// Fill out your copyright notice in the Description page of Project Settings.

#include "FighterComponent.h"

// Engine Includes

// Game Includes

#pragma region Engine Callbacks


// Sets default values for this component's properties
UFighterComponent::UFighterComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFighterComponent::BeginPlay() {
	Super::BeginPlay();

	// ...

}


// Called every frame
void UFighterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

#pragma endregion

void UFighterComponent::StartBattle(ABattle* battle) {
	_Battle = battle;
	DrawStartingHand();
}

void UFighterComponent::DrawStartingHand() {
	// Do nothing
}

void UFighterComponent::DrawNextGem() {
	FGemDefinition gemDefinition = Bag.Pop();
	_Hand.Push(gemDefinition);
	AfterGemDrawn(gemDefinition);
}

void UFighterComponent::AfterGemDrawn(FGemDefinition gemDefinition) {}



