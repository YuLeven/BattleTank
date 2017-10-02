// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	TrackMaxDrivingForce = 400000.f;
}

void UTankTrack::SetThrottle(float Throttle)
{ 
	FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	FVector TrackLocation = GetComponentLocation();
	UE_LOG(LogTemp, Warning, TEXT("Applied throttle of %s to %s"), *ForceApplied.ToString(), *GetName())
	UPrimitiveComponent* RootTank = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	RootTank->AddForceAtLocation(ForceApplied, TrackLocation);
}


