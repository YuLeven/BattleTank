// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

UTankBarrel::UTankBarrel()
{
	//Turret's default settings
	MaxDegreesPerSecond = 20.f;
	MinEvelationDegrees = 0.f;
	MaxElevationDegrees = 40.f;
}

void UTankBarrel::Elevate(float DegreesPerSecond)
{
	UE_LOG(LogTemp, Warning, TEXT("Elevating..."))
}