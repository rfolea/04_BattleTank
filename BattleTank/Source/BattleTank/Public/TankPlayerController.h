// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"  // must be the last one

// Forward Declaration
class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected: // so subclasses can access it
	UFUNCTION(BluePrintCallable, Category = "Setup")
	ATank* GetControlledTank() const;

private:
	void BeginPlay() override;  // override checks to make sure you are using the right function from higher up in the heirarchy.
								// begin play is in AActor ...
								// In Actor, BeginPlay was written as a Virtual function which says it can be overwritten by any ansestor

	virtual void Tick(float DeltaTime) override;  // virtual is optional - says if we made a child of this onew any child could use it.
													// override makes sure there IS a overridable routine in the parent class

	// Start teh tank moving the barrel so that a shot would hit where the sroosshair intersects the world.
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& HitLocation) const; // return an OUT Parameter, true if llandscape hit

	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly)
		float CrossHairYLocation = 0.3333f;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000; // Max Range of line trace for aiming tank (10Km in cm)

};