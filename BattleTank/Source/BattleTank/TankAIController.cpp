// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("Tank AI reporting for duty!"));
	ATank* PlayerTank = GetPlayerTank();
	if (PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("The player tank is: %s"), *PlayerTank->GetName());
	}
}

ATank* ATankAIController::GetPlayerTank() const
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (PlayerController)
	{
		return Cast<ATank>(PlayerController->GetControlledPawn());
	}

	return nullptr;
}
