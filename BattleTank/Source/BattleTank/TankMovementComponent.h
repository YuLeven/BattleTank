// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:

	UTankMovementComponent();

	// Auxiliary method used to set the needed references.
	// I'd rather see the constructor used for this kind of stuff but
	// apparently this kind of thing is common here thanks to blueprint.
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	// This moves the tank forwards and backwards in a fly-by-wire system
	UFUNCTION(BlueprintCallable, Category = Movement)
	void IntendMoveForward(float Throw);

	// This rotates the tank clockwise in the fly-by-wire system
	UFUNCTION(BlueprintCallable, Category = Movement)
	void IntendTurnRight(float Throw);

	// This rotates the tank anti-clockwise in the fly-by-wire system
	UFUNCTION(BlueprintCallable, Category = Movement)
	void IntendTurnLeft(float Throw);
	
private:

	UPROPERTY()
	class UTankTrack* LeftTrack;
	UTankTrack* RightTrack;

	// This method is called by the AI when it is standing on a nav mesh bound volume every frame (pathfinding)
	// The passed vector is the direction needed to be followed in order to reach the target
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
};
