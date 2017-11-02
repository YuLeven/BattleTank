// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	UTankTurret();

	// Rotates the turrent, -1 meaning hard left and +1 hard right
	void Rotate(float RelativeSpeed);

private:

	// Sets up the maximum allowed speed of elevation for the barrel
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond;

};
