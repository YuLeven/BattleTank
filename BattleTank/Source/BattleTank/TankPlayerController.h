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

	class ATank* GetControlledTank() const;

private:

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation;

	UPROPERTY(EditAnywhere)
	float CrosshairYLocation;

	UPROPERTY(EditAnywhere)
	float LineTraceRange;

	void AimTowardsCrosshair();

	//True if hit anythin, takes an out parameter to point the hit location
	bool GetSightRayLocation(FVector& HitLocation) const;

	//True if it managed to get the look direction
	bool GetLookDirection(const FVector2D CrosshairPosition, FVector& LookDirection) const;

	//True if the unit vector is pointing to anything hittable
	bool GetLookVectorHitLocation(const FVector WorldDirection, FVector& HitLocation) const;
	
};
