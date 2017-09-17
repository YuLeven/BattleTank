// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Causes the projectile to launch
	void Launch(float LaunchSpeed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	class UTankProjectileMovementComponent* TankProjectileMovementComponent;

};
