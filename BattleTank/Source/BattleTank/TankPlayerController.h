// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	//Constructor
	ATankPlayerController();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// This is the player's tank
	class ATank* GetControlledTank() const;

private:

	// Sets where the crosshair will sit vertically
	UPROPERTY(EditAnywhere)
	float CrosshairXLocation;

	// Sets where the crosshair will sit horizontally
	UPROPERTY(EditAnywhere)
	float CrosshairYLocation;

	// This is used for ray-traycing, setting the distance 
	// between the crosshair and an actor it might aim at
	UPROPERTY(EditAnywhere)
	float LineTraceRange;

	// Gets a HitLocation to the object aimed by the crosshair
	void AimTowardsCrosshair();

	// True if hit anything, takes an out parameter to point the hit location
	bool GetSightRayLocation(FVector& HitLocation) const;

	// True if it managed to get the look direction
	bool GetLookDirection(const FVector2D CrosshairPosition, FVector& LookDirection) const;

	// True if the unit vector is pointing to anything hittable
	bool GetLookVectorHitLocation(const FVector WorldDirection, FVector& HitLocation) const;
	
};
