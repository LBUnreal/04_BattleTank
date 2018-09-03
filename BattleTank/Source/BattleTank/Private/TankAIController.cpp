// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ATank* tank = GetAIControlledTank();
	ATank* playerTank = GetPlayerControlledTank();
}


ATank* ATankAIController::GetAIControlledTank() const
{
	return (Cast<ATank>(GetPawn()));
}

ATank* ATankAIController::GetPlayerControlledTank() const
{
	return (Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn()));
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (GetPlayerControlledTank())
	{
		//TODO; Move towards the player

		//Aim Towards the player
		GetAIControlledTank()->AimAt(GetPlayerControlledTank()->GetActorLocation());

		//Fire if ready
	}
}

