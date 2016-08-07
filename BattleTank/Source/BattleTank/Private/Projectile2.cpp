// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Projectile2.h"


// Sets default values
AProjectile2::AProjectile2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovement->bAutoActivate = false;  // don't create until we say so (when we fire it)

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);  // pre-check "Simulation Generates Hit Event" in BP
	CollisionMesh->SetVisibility(false);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LaunchBlast->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile2::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AProjectile2::LaunchProjectile(float Speed)
{
	//In Tank.cpp we have the projectile a location and rotation, so now just use the forward vcector ...
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector*Speed);
	ProjectileMovement->Activate(); // Activate the motion
}