// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"  // can't use forward reference because we are actually calling a method below ...
#include "TankTurret.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;  

	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
//	auto OurTankName = GetOwner()->GetName(); // comes out as an FString
//	auto BarrelLocation = Barrel->GetComponentLocation().ToString();
//	UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *OurTankName, *HitLocation.ToString(), *BarrelLocation);

	if (!ensure(Barrel)) { return; } // protect our barrel reference

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolutiuon = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0, // don't override gravity
		ESuggestProjVelocityTraceOption::DoNotTrace
	); 
	
	if (bHaveAimSolutiuon)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);

//		auto TankName = GetOwner()->GetName();
//		auto Time = GetWorld()->GetTimeSeconds();
//		UE_LOG(LogTemp, Warning, TEXT("Tank %s Aiming at %s"),*TankName, *AimDirection.ToString());
	}
		// No Aim Solution Found
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel && Turret)) { return; }

	// Work out difference between current barrel rotation and aim direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();  // tells us pitch yaw and roll of current barrel 
	auto AimAsRotator = AimDirection.Rotation();                 // Aim direction sis where we need to be to shoot.
	auto DeltaRotator = AimAsRotator - BarrelRotator;            // So this is the difference bwetween them

	Barrel->Elevate(DeltaRotator.Pitch); 
	Turret->Rotate(DeltaRotator.Yaw);

	return;
}