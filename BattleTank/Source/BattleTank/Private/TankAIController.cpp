// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

/*	auto ControlledTank = GetAITank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller Can't find player tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("The Player Tank is: %s"), *(ControlledTank->GetName()));
	}  */

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Didn't find Playerr Tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Found First Player Controller: %s"), *(PlayerTank->GetName()));
	}  

//	UE_LOG(LogTemp, Warning, TEXT("AIController Begin Play"));
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(GetPlayerTank())
	{
		//TODO Move Towards Player

		// Aim Towards player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
		// Fire if ready
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
//	return Cast<ATank>(GetWorld()->GetFirstPlayerController());
	
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank>(PlayerPawn);
}

