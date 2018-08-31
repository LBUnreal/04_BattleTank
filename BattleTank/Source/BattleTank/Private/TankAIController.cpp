// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ATank* tank = GetAIControlledTank();

	if (tank == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not find AI controlled tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("found AI controlled tank: %s"), *tank->GetName());
	}

	ATank* playerTank = GetPlayerControlledTank();

	if (playerTank == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI could not find player controlled tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI found Player controlled tank: %s"), *playerTank->GetName());
	}
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

