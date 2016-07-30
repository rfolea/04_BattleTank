// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{

	// move barrel the right amount this frame
	// given a max elevation and frame time
//	auto Time = GetWorld()->GetTimeSeconds();
//	UE_LOG(LogTemp, Warning, TEXT("%f: Barrel->Elevate Called at speed %f"),Time, RelativeSpeed);

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	// Elevation Change we need this frame
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	// Calc raw elevation before limiting (clamping)
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange; // RelativeRotation is a propert of the scene component

	auto ClampedElevation = FMath::Clamp<float>(RawNewElevation, MinElevationInDegree, MaxElevationInDegrees);

	SetRelativeRotation(FRotator(ClampedElevation, 0, 0));

}

