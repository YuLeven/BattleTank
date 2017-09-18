// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

	// Sets default values for this pawn's properties
	ATank();

	// Causes the barrel and turret to move to a designed hit location
	void AimAt(const FVector& HitLocation);

	// Sets the tank barrel to be controlled by this class
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	// Sets the tank turret to be controlled by this class
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet);

	// Causes the tank to fire a projectile
	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

protected:

	// Returns a pointer to this tank's aimiming component class
	UPROPERTY()
	class UTankAimingComponent* TankAimingComponent;

private:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Returnes true if the tank is reloaded (ready to fire)
	FORCEINLINE bool IsReloaded();

	// This determinates how fast (and thus how far) the project will go once fired
	UPROPERTY(EditAnywhere, Category = Firing)
	float ProjectileLaunchSpeed;

	// This is the projectile that will be fired from the barrel
	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<class AProjectile> ProjectileBlueprint;

	// This is the time in seconds between shots
	UPROPERTY(EditAnywhere)
	float ReloadTimeInSeconds;

	// This is used to store the last time the tank fired a projectile
	// and will be used by IsReloaded() to indicate wether it's ready
	// to fire again
	double LastFireTime;
	
};
