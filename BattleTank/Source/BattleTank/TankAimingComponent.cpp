// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
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
	//Return early if there's no Barrel
	if (!Barrel) return;

	FVector OutLaunchVelocity;
	bool bSucceededCalculatingLaunchVelocity = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		Barrel->GetSocketLocation(FName("Projectile")),
		HitLocation,
		ProjectileLaunchSpeed,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bSucceededCalculatingLaunchVelocity)
	{
		MoveBarrelTowards(OutLaunchVelocity.GetSafeNormal());
	}

}


void UTankAimingComponent::MoveBarrelTowards(const FVector& AimDirection)
{
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator AimAsARotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsARotator - BarrelRotation;
	Barrel->Elevate(5.f);
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

