// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"


UTankMovementComponent::UTankMovementComponent()
{
	LeftTrack = nullptr;
	RightTrack = nullptr;
}

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!ensure(LeftTrackToSet && RightTrackToSet)) return;

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}



void UTankMovementComponent::IntendMoveForward(float Throw)
{
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	// Force is applied the opposite track relative to the direction we want to go
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::IntendTurnLeft(float Throw)
{
	// Force is applied the opposite track relative to the direction we want to go
	RightTrack->SetThrottle(Throw);
	LeftTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AIMovementForward = MoveVelocity.GetSafeNormal();

	// We feed the cross product of the tank forward and the player direction onto IntendTurnRight
	// to cause the AI tanks to try to be facing to the player at every frame
	IntendTurnRight(
		FVector::CrossProduct(
			TankForward,
			AIMovementForward
		).Z
	);

	// We feed the dot product of the aforementioned vectors to cause
	// the AI tanks to try to be parallel to the player at every frame
	IntendMoveForward(
		FVector::DotProduct(TankForward, AIMovementForward)
	);
}
