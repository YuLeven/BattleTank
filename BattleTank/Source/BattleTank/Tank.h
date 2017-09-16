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

	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// This determinates how fast (and thus how far) the project will go once fired
	UPROPERTY(EditAnywhere, Category = "Firing")
	float ProjectileLaunchSpeed;
	
};
