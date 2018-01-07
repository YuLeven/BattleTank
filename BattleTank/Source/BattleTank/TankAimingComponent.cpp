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

	FiringState = EFiringState::Locked;

	// ...
}

void UTankAimingComponent::AimAt(const FVector& HitLocation, float ProjectileLaunchSpeed)
{
	// Return early if there's no Barrel or Turret
	// This should be set externally by the class composing itself with UTankAimingComponent
	// TODO: Make an assertion here? This should always be set.
	auto BasicMessage = FString(TEXT("static mesh component reference is not set in TankAimimingComponent. It won't move until it's set from blueprint"));
	if (!ensure(Barrel && Turret)) return;

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
	if (!bSucceededCalculatingLaunchVelocity) return;

	MoveBarrelTowards(OutLaunchVelocity.GetSafeNormal());
	MoveTurretTowards(OutLaunchVelocity.GetSafeNormal());
}

FRotator UTankAimingComponent::CalculateDeltaRotator(const FRotator& RotatorA, const FRotator& RotatorB)
{
	return RotatorA - RotatorB;
}

void UTankAimingComponent::MoveBarrelTowards(const FVector& AimDirection)
{
	if (!ensure(Barrel)) return;
	FRotator DeltaRotator = CalculateDeltaRotator(AimDirection.Rotation(), Barrel->GetForwardVector().Rotation());
	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurretTowards(const FVector& AimDirection)
{
	if (!ensure(Turret)) return;
	FRotator DeltaRotator = CalculateDeltaRotator(AimDirection.Rotation(), Turret->GetForwardVector().Rotation());
	Turret->Rotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

