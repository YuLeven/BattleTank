// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Tank.h"

ATankAIController::ATankAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	// This method call returns the NULL macro should it fail to find a player controller
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (PlayerController)
	{
		return Cast<ATank>(PlayerController->GetPawn());
	}

	return nullptr;
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ATank* PlayerTank = GetPlayerTank();
	
	// If we managed to find the player tank, aim at him
	if (PlayerTank != nullptr)
	{
		GetControlledTank()->AimAt(PlayerTank->GetActorLocation());
		// Fire 
		GetControlledTank()->Fire();
	}
	
}
