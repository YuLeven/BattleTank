// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:

	ATankAIController();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called once the game starts
	virtual void BeginPlay() override;

	// Tank Aiming Component
	UPROPERTY()
	class UTankAimingComponent* TankAimingComponent;

};
