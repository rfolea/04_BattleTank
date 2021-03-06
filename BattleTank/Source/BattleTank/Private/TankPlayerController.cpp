// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"

// Tick
// Super
// AimTowardsCrosshair


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass <UTankAimingComponent>();
	if (!ensure(AimingComponent)) {	return;	}
		FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
//	UE_LOG(LogTemp, Warning, TEXT("TankPlayerController Tick Method"));
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; }  // e.g. if not possesing. Maybe tank dies, so don't sue ensure ...
	auto AimingComponent = GetPawn()->FindComponentByClass <UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	
	FVector HitLocation;  //Out parameter
	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);

	if (bGotHitLocation) // Doesn't change anything, but does ray trace and if true log it out.
	{
		AimingComponent->AimAt(HitLocation);
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
		return GetLookVectorHitLocation( LookDirection, HitLocation);
	}

	return false;
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

