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

	if (!ensure(PlayerController)) return nullptr;
	
	return Cast<ATank>(PlayerController->GetPawn());
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ATank* PlayerTank = GetPlayerTank();
	if (!ensure(PlayerTank)) return;
	
	//Moves towards the player tank
	MoveToActor(PlayerTank, 30.f * 100.f);

	GetControlledTank()->AimAt(PlayerTank->GetActorLocation());
	// Fire 
	GetControlledTank()->Fire();
}
