// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Camera/PlayerCameraManager.h"

ATankPlayerController::ATankPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	CrosshairXLocation = 0.5f;
	CrosshairYLocation = 0.33333f;
	LineTraceRange = 1000000.f;
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(TankAimingComponent)) return;
	FoundAimingComponent(TankAimingComponent);
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(TankAimingComponent)) return;

	FVector HitLocation;
	if (GetSightRayLocation(HitLocation))
	{
		TankAimingComponent->AimAt(HitLocation);
	};
}

bool ATankPlayerController::GetSightRayLocation(FVector& HitLocation) const
{
	//Finds the crosshair position on the viewport
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D CrosshairScreenPosition(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	
	FVector WorldDirection; 
	if (GetLookDirection(CrosshairScreenPosition, WorldDirection))
	{
		return GetLookVectorHitLocation(WorldDirection, HitLocation);
	}

	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(const FVector WorldDirection, FVector& HitLocation) const
{
	FHitResult HitResult;

	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + WorldDirection * LineTraceRange;

	bool DidHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECC_Visibility
	);

	if (DidHit)
	{
		HitLocation = HitResult.Location;
	}
	else
	{
		HitLocation = FVector(0);
	}

	//Line trace didn't suceed
	return DidHit;
}

bool ATankPlayerController::GetLookDirection(const FVector2D CrosshairScreenPosition, FVector& LookDirection) const
{
	//Tries to retrieve the look direction
	FVector CameraWorldLocation; //This will be discarded
	return DeprojectScreenPositionToWorld(
		CrosshairScreenPosition.X, 
		CrosshairScreenPosition.Y, 
		CameraWorldLocation, 
		LookDirection
	);
}
