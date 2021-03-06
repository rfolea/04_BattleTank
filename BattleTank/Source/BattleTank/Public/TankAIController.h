// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
	// How close can the AI tank get to the player
	UPROPERTY(EditDefaultsOnly, category = "Setup") 
		float AcceptanceRadius = 8000;
	
private:

	void BeginPlay() override;  // override checks to make sure you are using the right function from higher up in the heirarchy.
								// begin play is in AActor ...
								// In Actor, BeginPlay was written as a Virtual function which says it can be overwritten by any ansestor

	virtual void SetPawn(APawn* InPawn) override;  // Gets called when the pawn gets possed

	virtual void Tick(float DeltaTime) override;  // virtual is optional - says if we made a child of this onew any child could use it.
												  // override makes sure there IS a overridable routine in the parent class

	UFUNCTION()
		void OnPossedTankDeath(); // Thi is what's going to get called when Tank Boradcasts it's death.

};
