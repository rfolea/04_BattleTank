// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward Declarations
class UTankBarrel;            
class UTankAimingComponent;
class AProjectile2;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();                  // will always fire in direction barrel is pointing, so no need for params

protected:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;
	
private:
	// Sets default values for this pawn's properties
	ATank();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile2> ProjectileBlueprint;
	//	UClass* ProjectileBlueprint; // Alternative - see lecture note TSubclass of ...

	// TODO - Remove after firing is moved to aiming component
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000; 


	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float RelaodTimeInSeconds = 3;
	
    // local barrel reference for spawing projectile
	UTankBarrel* Barrel = nullptr; // TODO - Remove this later


	double LastFireTime = 0;
};
