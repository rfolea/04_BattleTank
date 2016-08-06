// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"  // can't use forward reference because we are actually calling a method below ...
#include "TankTurret.h"
#include "Projectile2.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;  

	// ...
}

void UTankAimingComponent::BeginPlay()
{
//	Super::BeginPlay();
	// So first fire is after inital re-laod
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)  // could also use GewtWorld()->GetTimeInSeconds() ...
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}


bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01);
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
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
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);

//		auto TankName = GetOwner()->GetName();
//		auto Time = GetWorld()->GetTimeSeconds();
//		UE_LOG(LogTemp, Warning, TEXT("Tank %s Aiming at %s"),*TankName, *AimDirection.ToString());
	}
		// No Aim Solution Found
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel) || !ensure(Turret)) { return; }

	// Work out difference between current barrel rotation and aim direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();  // tells us pitch yaw and roll of current barrel 
	auto AimAsRotator = AimDirection.Rotation();                 // Aim direction sis where we need to be to shoot.
	auto DeltaRotator = AimAsRotator - BarrelRotator;            // So this is the difference bwetween them

	Barrel->Elevate(DeltaRotator.Pitch); 
	Turret->Rotate(DeltaRotator.Yaw);

	return;
}

void UTankAimingComponent::Fire()
{
	if (FiringState != EFiringState::Reloading) {
		// else spawn a projectile at socket location
		if (!ensure(Barrel )) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		auto Projectile =
			GetWorld()->SpawnActor<AProjectile2>(
				ProjectileBlueprint,
				Barrel->GetSocketLocation(FName("Projectile")),  // Copied FName from Barrel BP socket name
				Barrel->GetSocketRotation(FName("Projectile"))  // Copied FName from Barrel BP socket name
				);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}

}
