// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	//Constructor
	ATankPlayerController();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class ATank* GetControlledTank() const;
	
	void AimTowardsCrosshair() const;
	
};
