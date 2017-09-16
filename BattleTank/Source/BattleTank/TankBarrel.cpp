// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Runtime/Engine/Classes/Engine/World.h"

UTankBarrel::UTankBarrel()
{

	PrimaryComponentTick.bCanEverTick = false;

	// Turret's default settings
	// They're blueprint editable, so go edit them there
	MaxDegreesPerSecond = 5.f;
	MinEvelationDegrees = 0.f;
	MaxElevationDegrees = 40.f;
}

void UTankBarrel::Elevate(float RelativeSpeed)
{
	float ElevationChange = FMath::Clamp(RelativeSpeed, -1.f, 1.f) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	SetRelativeRotation(FRotator(
		FMath::Clamp(RawNewElevation, MinEvelationDegrees, MaxElevationDegrees), 
		0, 
		0
	));
}