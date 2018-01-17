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
	void AimAt(const FVector& HitLocation);

	// Causes the tank to fire a projectile
	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

	// Returns the pointer to the barrel being manipulated by this class
	FORCEINLINE UTankBarrel* GetBarrelReference() { return Barrel; }

	// Factory method used to initialize the TankAimingComponentClass
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* Barrel, UTankTurret* Turret);

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	virtual void BeginPlay() override;

protected:

	// This defines the current aiming state of the tank
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState;

private:

	// Moves the barrel in vertically the diretion according to the AimDirection unit vector
	void MoveBarrelTowards(const FVector& AimDirection);

	// Moves the turrent horizontally in the diretion according to the AimDirection unit vector
	void MoveTurretTowards(const FVector& AimDirection);

	FORCEINLINE FRotator CalculateDeltaRotator(const FRotator& RotatorA, const FRotator& RotatorB);

	// Returnes true if the tank is reloaded (ready to fire)
	FORCEINLINE bool IsReloaded();

	// Returns true if the tank barrel is moving
	FORCEINLINE bool IsBarrelMoving();

	// This is the barrel which will be acted upon by the methods in this class
	UPROPERTY()
	UTankBarrel* Barrel;

	// This is the turret which will be actec upon by the methods in this class
	UPROPERTY()
	UTankTurret* Turret;

	// This determinates how fast (and thus how far) the project will go once fired
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ProjectileLaunchSpeed;

	// This is the projectile that will be fired from the barrel
	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<class AProjectile> ProjectileBlueprint;

	// This is the time in seconds between shots
	UPROPERTY(EditAnywhere)
	float ReloadTimeInSeconds;

	// This is used to determine the aim direction of the barrel
	UPROPERTY()
	FVector AimDirection;

	// This is used to store the last time the tank fired a projectile
	// and will be used by IsReloaded() to indicate wether it's ready
	// to fire again
	double LastFireTime;
	
};
