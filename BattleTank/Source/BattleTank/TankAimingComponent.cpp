// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::AimAt(const FVector& HitLocation, float ProjectileLaunchSpeed)
{
	// Return early if there's no Barrel
	// This should be set externally by the class composing itself with UTankAimingComponent
	// TODO: Make an assertion here? This should always be set.
	if (!Barrel) return;

	FVector OutLaunchVelocity;
	bool bSucceededCalculatingLaunchVelocity = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		Barrel->GetSocketLocation(FName("Projectile")),
		HitLocation,
		ProjectileLaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	// If we managed to calculate a launch velocity, move the barrel towards its direction
	if (bSucceededCalculatingLaunchVelocity)
	{
		MoveBarrelTowards(OutLaunchVelocity.GetSafeNormal());
		MoveTurretTowards(OutLaunchVelocity.GetSafeNormal());
	}

}

FRotator UTankAimingComponent::CalculateDeltaRotator(const FRotator& RotatorA, const FRotator& RotatorB)
{
	return RotatorA - RotatorB;
}

void UTankAimingComponent::MoveBarrelTowards(const FVector& AimDirection)
{
	
	if (Barrel == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Barrel static mesh component reference is not set in TankAimimingComponent. It won't move until it's set from blueprint"))
		return;
	}

	FRotator DeltaRotator = CalculateDeltaRotator(AimDirection.Rotation(), Barrel->GetForwardVector().Rotation());
	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurretTowards(const FVector& AimDirection)
{
	if (Turret == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Turret static mesh component reference is not set in TankAimimingComponent. It won't move until it's set from blueprint"))
		return;
	}

	FRotator DeltaRotator = CalculateDeltaRotator(AimDirection.Rotation(), Turret->GetForwardVector().Rotation());
	Turret->Rotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
}

