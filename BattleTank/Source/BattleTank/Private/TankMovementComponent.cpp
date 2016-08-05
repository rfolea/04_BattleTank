// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	//auto Time = GetWorld()->GetTimeSeconds();
	//auto Name = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("Intend Move Forward Throw: %f"), Throw)

	if (!LeftTrack || !RightTrack) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing Left or Right TankTrack Pointer"), Throw)
		return;
	}
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call super - we are replacing functionality

	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();  // Current Heading - unit vector direction relative to the global
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();                  // Direction we WANT to be heading    

	float ForwardVelocity = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveForward(ForwardVelocity);

	float RotateVelocity = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendTurnRight(RotateVelocity);

	auto TankName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s   Rotating to: %f"), *TankName, RotateVelocity);
}