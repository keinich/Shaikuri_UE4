// Copyright Rafael Weschle

#include "GrabberComponent.h"

// Engine Includes
#include "Runtime/Engine/Classes/Engine/World.h "
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h "

// Sets default values for this component's properties
UGrabberComponent::UGrabberComponent() {
  // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
  // off to improve performance if you don't need them.
  PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabberComponent::BeginPlay() {
  Super::BeginPlay();
  FindPhysicsHandleComponent();
  SetUpInputComponent();
}

void UGrabberComponent::SetUpInputComponent() {
   // Look for the Input Component
  InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
  if (InputComponent) {
    UE_LOG(LogTemp, Warning, TEXT("Input-Component found"));
    //Bind the input action
    InputComponent->BindAction("Grab", EInputEvent::IE_Pressed, this, &UGrabberComponent::Grab);
    InputComponent->BindAction("Grab", EInputEvent::IE_Released, this, &UGrabberComponent::Release);
  }
  else {
    UE_LOG(
      LogTemp, Error,
      TEXT("%s missing Input component"),
      *(GetOwner()->GetName())
    );
  }
}

void UGrabberComponent::FindPhysicsHandleComponent() {
  /// Look for the Physics Handle Component
  PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
  if (PhysicsHandle == nullptr) {
    UE_LOG(
      LogTemp,
      Error,
      TEXT("%s missing Physics handle component"),
      *(GetOwner()->GetName())
    );
  }
}

void UGrabberComponent::Grab() {
  UE_LOG(LogTemp, Warning, TEXT("Grabbing!"));

  /// LINE TRACE and see if we reach any actors with physics body collision channel set
  FHitResult HitResult = GetFirstPhysicsBodyInReach();
  auto ComponentToGrab = HitResult.GetComponent();
  auto ActorHit = HitResult.GetActor();

  /// If we hit something then attach a physics handle
  if (ActorHit) {
    if (!PhysicsHandle) { return; }
    PhysicsHandle->GrabComponent(
      ComponentToGrab,
      NAME_None,
      ComponentToGrab->GetOwner()->GetActorLocation(),
      true
    );
  }
}

void UGrabberComponent::Release() {
  if (!PhysicsHandle) { return; }
  PhysicsHandle->ReleaseComponent();
}

// Called every frame
void UGrabberComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

  if (!PhysicsHandle) { return; }

  //if the physics handle is attachedif
  if (PhysicsHandle->GrabbedComponent) {
    // move the object that were holding  
    PhysicsHandle->SetTargetLocation(GetReachLineEnd());
  }
}

const FHitResult UGrabberComponent::GetFirstPhysicsBodyInReach() {
  /// Line-trace (AKA Ray-cast) out to reach distance
  FHitResult HitResult;
  FCollisionQueryParams queryParams(FName(TEXT("")), false, GetOwner());
  GetWorld()->LineTraceSingleByObjectType(
    OUT HitResult,
    GetReachLineStart(),
    GetReachLineEnd(),
    FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
    queryParams
  );
  return HitResult;
}

FVector UGrabberComponent::GetReachLineStart() {
  /// Get player view point
  FVector PlayerViewPointLocation;
  FRotator PlayerViewPointRotation;
  GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
    OUT PlayerViewPointLocation,
    OUT PlayerViewPointRotation
  );

  return PlayerViewPointLocation;
}

FVector UGrabberComponent::GetReachLineEnd() {
  /// Get player view point
  FVector PlayerViewPointLocation;
  FRotator PlayerViewPointRotation;
  GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
    OUT PlayerViewPointLocation,
    OUT PlayerViewPointRotation
  );

  //How far ahead of the player can we reach in cm  
  FVector RotationVector = PlayerViewPointRotation.Vector() * Reach;

  return PlayerViewPointLocation + RotationVector;
}
