// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* tank = GetControlledTank();

	if (tank == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not find player controlled tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("found tank player controller: %s"), *tank->GetName());
	}

}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


