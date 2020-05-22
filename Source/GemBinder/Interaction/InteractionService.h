// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

	// Engine Includes
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// Game Includes

// Last Include
#include "InteractionService.generated.h"

// Forward Declarations

UCLASS()
class SHAIKURI_API AInteractionService : public AActor
{
	GENERATED_BODY()

#pragma region Engine Callbacks

public:
	// Sets default values for this actor's properties
	AInteractionService();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
#pragma endregion

public: // UFunctions

	UFUNCTION(BlueprintCallable, category = "Interaction")
		static void PresentInteractionText(const FText& text, UObject* worldContextObject);

	UFUNCTION(BlueprintCallable, category = "Interaction")
		static void StopPresentInteractionText(UObject* worldContextObject);

public: // UProperties

protected: // UFunctions

	UFUNCTION(BlueprintImplementableEvent, category = "Interaction")
		void PresentInteractionTextInternal(const FText& text);

	UFUNCTION(BlueprintImplementableEvent, category = "Interaction")
		void StopPresentInteractionTextInternal();

protected: // UProperties

private: // Functions

private: // Fields
};
