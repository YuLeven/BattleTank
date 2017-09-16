// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Runtime/Engine/Classes/Engine/World.h"

UTankTurret::UTankTurret()
{
	// Save some resources by not ticking the turret
	PrimaryComponentTick.bCanEverTick = false;

	// Turret's default settings
	// They're blueprint editable, so go edit them there
	MaxDegreesPerSecond = 15.f;
}

void UTankTurret::Rotate(float RelativeSpeed)
{
	float OrientationChange = FMath::Clamp(RelativeSpeed, -1.f, 1.f) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	auto RawNewElevation = RelativeRotation.Yaw + OrientationChange;
	SetRelativeRotation(FRotator(
		0,
		RawNewElevation,
		0
	));
}


