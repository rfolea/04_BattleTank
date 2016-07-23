// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

// Tick
// Super
// AimTowardsCrosshair


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController Not Possessing"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possesing: %s"), *(ControlledTank->GetName()));
	}

	/*
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController Not Possessing"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possesing: %s"), *(ControlledTank->GetName()));
	}  */

//	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
//	UE_LOG(LogTemp, Warning, TEXT("TankPlayerController Tick Method"));
}


ATank* ATankPlayerController::GetControlledTank() const
	{
	return Cast<ATank>(GetPawn());
	}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank())
	{
		// Get world location through crosshair
		// If it hits something (ie landscape) 
			//Tell controlled tank to aim at this point. 
	}
	return;
}
