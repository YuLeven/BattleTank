// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	FiringState = EFiringState::Locked;
	ProjectileLaunchSpeed = 4000.f;
	ReloadTimeInSeconds = 3.f;
	Barrel = nullptr;
	Turret = nullptr;
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) return false;
	return !(Barrel->GetForwardVector().Equals(AimDirection), 0.001);
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!IsReloaded())
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	// Causes first fire to have to wait the delay defined by ReloadTimeInSeconds
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::AimAt(const FVector& HitLocation)
{
	// Return early if there's no Barrel or Turret
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

	AimDirection = OutLaunchVelocity.GetSafeNormal();

	MoveBarrelTowards(AimDirection);
	MoveTurretTowards(AimDirection);
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

bool UTankAimingComponent::IsReloaded()
{
	return ((FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds) || LastFireTime == NULL;
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel)) return;

	if (FiringState != EFiringState::Reloading)
	{
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")) + FVector(100.f, 0.f, 0.f),
			Barrel->GetSocketRotation(FName("Projectile"))
		);

		if (!ensure(Projectile)) return;

		Projectile->Launch(ProjectileLaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}