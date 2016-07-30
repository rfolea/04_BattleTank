// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"


void UTankTurret::Rotate(float RelativeSpeed)
{

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	// Rotation Change we need this frame
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	// Calc raw elevation before limiting (clamping)
	auto Rotation = RelativeRotation.Yaw + RotationChange; // RelativeRotation is a propert of the scene component

	SetRelativeRotation(FRotator(0, Rotation, 0));

}

