// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	TrackMaxDrivingForce = 650000.f;
}

void UTankTrack::SetThrottle(float Throttle)
{ 
	UE_LOG(LogTemp, Warning, TEXT("Applied throttle of %f to %s"), Throttle, *GetName())

	FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	FVector TrackLocation = GetComponentLocation();
	UPrimitiveComponent* RootTank = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	RootTank->AddForceAtLocation(ForceApplied, TrackLocation);
}


