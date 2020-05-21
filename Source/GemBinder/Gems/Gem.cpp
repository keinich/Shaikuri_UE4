// Fill out your copyright notice in the Description page of Project Settings.


#include "Gem.h"

#pragma region Engine Callbacks

// Sets default values
AGem::AGem() {
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  Capsule = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
  Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
  GemWidget = CreateDefaultSubobject<UWidgetComponent>("Gem Name Widget");

  SetRootComponent(Capsule);
  Mesh->SetupAttachment(Capsule);
  GemWidget->SetupAttachment(Capsule);

}

// Called when the game starts or when spawned
void AGem::BeginPlay() {
  Super::BeginPlay();

}

// Called every frame
void AGem::Tick(float DeltaTime) {
  Super::Tick(DeltaTime);

}

#pragma endregion



