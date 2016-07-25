// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"


void UTankBarrel::Elevate(float DegreesPerSecond)
{

	// move barrel the right amount this frame
	// given a max elevation and frame time
	UE_LOG(LogTemp, Warning, TEXT("Barrel->Elevate Called at speed %f"), DegreesPerSecond);
}

