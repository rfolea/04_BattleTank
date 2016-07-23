// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"  // must be the last one


UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATank* GetControlledTank() const;

	void BeginPlay() override;  // override checks to make sure you are using the right function from higher up in the heirarchy.
								// begin play is in AActor ...
								// In Actor, BeginPlay was written as a Virtual function which says it can be overwritten by any ansestor

	virtual void Tick(float DeltaTime) override;  // virtual is optional - says if we made a child of this onew any child could use it.
													// override makes sure there IS a overridable routine in the parent class

	// Start teh tank moving the barrel so that a shot would hit where the sroosshair intersects the world.
	void AimTowardsCrosshair();

private:
	bool GetSightRayHitLocation(FVector& HitLocation) const; // return an OUT Parameter, true if llandscape hit

};