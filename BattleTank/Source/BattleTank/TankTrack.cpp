// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
	TrackMaxDrivingForce = 400000.f;
}

bool UTankTrack::IsOnGround()
{
	return GetWorld()->LineTraceTestByChannel(
		GetComponentLocation(),
		GetComponentLocation() + FVector(0.f, 0.f, -20.f),
		ECollisionChannel::ECC_Visibility
	);
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// Add the force to the tank to prevent it from slipping sideways
	if (IsOnGround())
	{
		ApplySidewaysForceToPreventSlippage(DeltaTime);
	}
}

void UTankTrack::ApplySidewaysForceToPreventSlippage(float DeltaTime)
{
	// This is the component (the tank) to which the forces will be added
	UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	// The dot product between the track's right vector (the one pointing out of it) and the
	// tank's velocity (represented by the track's own velocity, since the whole thing is moving in one single mass)
	// determines how much the tank is slipping sideways. A value of zero indicates no slippage at all.
	float SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	// The correction acceleration is calculated dividing the delta time by the prodcut found before
	// multiplied by the outer vector. We also multiply this by -1 to make it an opposite force to the current acceleration
	FVector CorrectionAcceleration = (SlippageSpeed / DeltaTime * GetRightVector()) * -1;

	// The correction force is then multiplied by the tank's mass and divided by two (since we have to tracks)
	FVector CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2;

	// Finally, we add the force to the tank to prevent it from slipping sideways
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	if (IsOnGround()) 
	{
		FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
		FVector TrackLocation = GetComponentLocation();
		UPrimitiveComponent* RootTank = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
		RootTank->AddForceAtLocation(ForceApplied, TrackLocation);
	}
}


