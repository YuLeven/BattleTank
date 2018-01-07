// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "Runtime/Engine/Classes/Engine/World.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// These are merely sensible defaults. Don't change then here. Go do it on the tank BP
	ProjectileLaunchSpeed = 4000.f;
	ReloadTimeInSeconds = 3.f;
}

bool ATank::IsReloaded()
{
	return ((FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds) || LastFireTime == NULL;
}

void ATank::Fire()
{
	
	UTankBarrel* Barrel = this->FindComponentByClass<UTankBarrel>();
	if (!ensure(Barrel)) return;
	
	if (IsReloaded())
	{
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")) + FVector(100.f, 0.f, 0.f),
			Barrel->GetSocketRotation(FName("Projectile"))
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

