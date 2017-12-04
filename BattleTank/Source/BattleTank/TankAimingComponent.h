// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Aiming states
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Uses the hit location and projectile launch speed to move the barrel in
	// the direction of the to-be hit actor
	UFUNCTION(BluePrintCallable)
	void AimAt(const FVector& HitLocation, float ProjectileLaunchSpeed);

	// Returns the pointer to the barrel being manipulated by this class
	FORCEINLINE UTankBarrel* GetBarrelReference() { return Barrel; }

	// Factory method used to initialize the TankAimingComponentClass
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* Barrel, UTankTurret* Turret);

protected:

	// This defines the current aiming state of the tank
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState;

private:

	// Moves the barrel in vertically the diretion according to the AimDirection unit vector
	void MoveBarrelTowards(const FVector& AimDirection);

	// Moves the turrent horizontally in the diretion according to the AimDirection unit vector
	void MoveTurretTowards(const FVector& AimDirection);

	// This is the barrel which will be acted upon by the methods in this class
	UPROPERTY()
	UTankBarrel* Barrel = nullptr;

	// This is the turret which will be actec upon by the methods in this class
	UPROPERTY()
	UTankTurret* Turret = nullptr;

	FORCEINLINE FRotator CalculateDeltaRotator(const FRotator& RotatorA, const FRotator& RotatorB);
	
};
