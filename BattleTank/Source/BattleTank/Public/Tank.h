// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward Declarations
class UTankBarrel;            
class AProjectile2;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();                  // will always fire in direction barrel is pointing, so no need for params

private:
	// Sets default values for this pawn's properties
	ATank();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile2> ProjectileBlueprint;
	//	UClass* ProjectileBlueprint; // Alternative - see lecture note TSubclass of ...

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float RelaodTimeInSeconds = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000;
	
    // local barrel reference for spawing projectile
	UTankBarrel* Barrel = nullptr; // TODO - Remove this later


	double LastFireTime = 0;
};
