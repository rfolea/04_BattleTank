// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
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

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet) 
{
	Barrel = BarrelToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
//	auto OurTankName = GetOwner()->GetName(); // comes out as an FString
//	auto BarrelLocation = Barrel->GetComponentLocation().ToString();
//	UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *OurTankName, *HitLocation.ToString(), *BarrelLocation);

	if (!Barrel) { return; } // protect our barrel reference

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity
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
			) // Calculate the out launch velocity
		)
	{ 
	
	auto AimDirection = OutLaunchVelocity.GetSafeNormal();
	auto TankName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("Tank %s Aiming at %s"),*TankName, *AimDirection.ToString());
	}
	//If No solution do nothing
}