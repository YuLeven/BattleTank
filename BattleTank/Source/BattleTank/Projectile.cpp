// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "TankProjectileMovementComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Fetches our aiming component
	TankProjectileMovementComponent = CreateDefaultSubobject<UTankProjectileMovementComponent>(FName("Projectile Movement Component"));

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectile::Launch(float LaunchSpeed)
{
	TankProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * LaunchSpeed);
	TankProjectileMovementComponent->Activate();
}

