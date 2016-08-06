// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// enum for aiming state
UENUM()
enum class EFiringState :uint8
{
	Reloading,
	Aiming,
	Locked
};

// Forward Declaration
class UTankBarrel; 
class UTankTurret;
class AProjectile2;

// Holds Barrel's properties and Elevate Method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet); // Used in Tank BP Event Graph

	void AimAt(FVector HitLocation);  // Tell the Tank to aim at a partiicular worldspace 

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();                // will always fire in direction barrel is pointing, so no need for params

protected:
	UPROPERTY(BlueprintReadOnly, category = "State")
	EFiringState FiringState = EFiringState::Locked;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	void	MoveBarrelTowards(FVector AimDirection);

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile2> ProjectileBlueprint;
	//	UClass* ProjectileBlueprint; // Alternative - see lecture note TSubclass of ...

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float RelaodTimeInSeconds = 3;

	double LastFireTime = 0;
};
