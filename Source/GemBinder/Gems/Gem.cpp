// Fill out your copyright notice in the Description page of Project Settings.


#include "Gem.h"

#pragma region Engine Callbacks

// Sets default values
AGem::AGem() {
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  Capsule = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
  Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
  GemNameWidget = CreateDefaultSubobject<UWidgetComponent>("Gem Name Widget");
  GemImageWidget = CreateDefaultSubobject<UWidgetComponent>("Gem Image Widget");
  GemDescriptionWidget = CreateDefaultSubobject<UWidgetComponent>("Gem Description Widget");

  SetRootComponent(Capsule);
  Mesh->SetupAttachment(Capsule);
  GemNameWidget->SetupAttachment(Capsule);
  GemImageWidget->SetupAttachment(Capsule);
  GemDescriptionWidget->SetupAttachment(Capsule);

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



