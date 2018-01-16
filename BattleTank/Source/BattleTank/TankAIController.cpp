// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "TankAimingComponent.h"

ATankAIController::ATankAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!ensure(PlayerController)) return;
	APawn* PlayerTank = PlayerController->GetPawn();
	if (!ensure(PlayerTank)) return;
	if (!ensure(TankAimingComponent)) return;
	
	// Moves towards the player tank
	MoveToActor(PlayerTank, 30.f * 100.f);
	// Aims at the player tank
	TankAimingComponent->AimAt(PlayerTank->GetActorLocation());
	// Fires at the aimed tank (if possible)
	TankAimingComponent->Fire();
}
