// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	// Calculate slippage speed - cross product
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity()); // "GetRightVector()" of THIS component

	// Work out required accel this frame to correct (speed over time)
	auto CorrectionAccelration = -SlippageSpeed / DeltaTime * GetRightVector();

	// Calculate and apply sideways force (F = M a)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAccelration) / 2;  // divide by two becasue there are two tracks
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();    // Location of this track - see BP xyz vector

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

	return;
}


