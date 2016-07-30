// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Projectile2.h"


// Sets default values
AProjectile2::AProjectile2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

