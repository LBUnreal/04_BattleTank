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
}


ATank* ATankAIController::GetAIControlledTank() const
{
	return (Cast<ATank>(GetPawn()));
}

