// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile2.generated.h"

UCLASS()
class BATTLETANK_API AProjectile2 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile2();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void LaunchProjectile(float Speed);

private:
	UProjectileMovementComponent* ProjectileMovement = nullptr;

};
