// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	//Class constructor. OCD tells me green stuff has to be here too.
	UTankBarrel();

	//Moves the barrel horizontally
	//-1 is max downward movenment, +1 is max upward movement
	void Elevate(float RelativeSpeed);

private:

	//Sets up the maximum allowed speed of elevation for the barrel
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond;

	//Determinates the maximum allowed elevation of aiming
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationDegrees;

	//Determinates the minimum allowed elevation of aiming
	UPROPERTY(EditAnywhere, Category = Setup)
	float MinEvelationDegrees;
	
};
