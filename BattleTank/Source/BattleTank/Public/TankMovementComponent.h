// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Responsible for driving the tank tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))  // So this component appears in anp BP custom menu
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet); // Used in Tank BP Event Graph

	UFUNCTION(BlueprintCallable, Category = "Input")                            // Used in Tank BP Input Setup
	void IntendMoveForward(float Throw);  // states intent to move

	UFUNCTION(BlueprintCallable, Category = "Input")                            // Used in Tank BP Input Setup
	void IntendTurnRight(float Throw);

private:

	// RequestDirectMove is a public method in the super class in teh UNavMovementComponent
	// Called from the pathfinding logic by the AI controllers
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	UTankTrack* LeftTrack = nullptr;  // priivate becasue they are sued in several different methods acrss the class
	UTankTrack* RightTrack = nullptr;
	
};
