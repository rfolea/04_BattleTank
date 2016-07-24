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
	if (!GetControlledTank()) { return; } // doesn't make sense to aim if we don't have a tank to aim ...
	

	FVector HitLocation;  //Out parameter

	if (GetSightRayHitLocation(HitLocation)) // Doesn't change anything, but does ray trace and if true log it out.
	{
		GetControlledTank()->AimAt(HitLocation);
	}

 
	
	return;
}


// Get world location of line trace through crosshair, true if it hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find crosshair position in pixel coordinates
	int32 ViewportsizeX, ViewportSizeY;
	GetViewportSize(ViewportsizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(CrossHairXLocation*ViewportsizeX, CrossHairYLocation*ViewportSizeY);

	// "De-Project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line trace along that look direction, and see what we hit(up to a max range)
		GetLookVectorHitLocation( LookDirection, HitLocation);
	}

	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if(GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility)
		) 
	{
		HitLocation = HitResult.Location;  // gets us to a FVector
		return true;
	}
	// Line Trace didn't succeed
	HitLocation = FVector(0); // just so we get known results coming out ...
	return false; 
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	// "De-Project" the screen position of the crosshair to a world direction
	FVector CameraWorldLocation;  // To be discarded
	return DeprojectScreenPositionToWorld
	(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		CameraWorldLocation, 
		LookDirection
	);
}

