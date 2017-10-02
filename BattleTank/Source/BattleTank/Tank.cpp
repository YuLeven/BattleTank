// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Projectile.h"
#include "Runtime/Engine/Classes/Engine/World.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Fetches our aiming component
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	
	// Fetches our movement component
	TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));

	// These are merely sensible defaults. Don't change then here. Go do it on the tank BP
	ProjectileLaunchSpeed = 4000.f;
	ReloadTimeInSeconds = 3.f;
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	UE_LOG(LogTemp, Warning, TEXT("Setting barrel"));
	TankAimingComponent->SetBarrelReference(BarrelToSet);
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	UE_LOG(LogTemp, Warning, TEXT("Setting turret"));
	TankAimingComponent->SetTurretReference(TurretToSet);
}

bool ATank::IsReloaded()
{
	return ((FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds) || LastFireTime == NULL;
}

void ATank::Fire()
{
	if (IsReloaded())
	{
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			TankAimingComponent->GetBarrelReference()->GetSocketLocation(FName("Projectile")) + FVector(100.f, 0.f, 0.f),
			TankAimingComponent->GetBarrelReference()->GetSocketRotation(FName("Projectile"))
			);

		Projectile->Launch(ProjectileLaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();
	}
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::AimAt(const FVector& HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, ProjectileLaunchSpeed);
}

