// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "Projectile2.h"
#include "TankAimingComponent.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s AELOF: C++ Tank Contructor"), *TankName);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();  // Needed for BP beginPlay to run ...

	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s AELOF: C++ Tank BeginPlay()"), *TankName);

	return;
}

void ATank::AimAt(FVector HitLocation)
{
	if (!ensure(TankAimingComponent)) { return; }
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	if (!ensure(Barrel)) { return; }
	bool isReloaded = (FPlatformTime::Seconds()-LastFireTime > RelaodTimeInSeconds);  // returns a double


	if (isReloaded) {
		// else spawn a projectile at socket location
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

