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
		UE_LOG(LogTemp, Warning, TEXT("found player controlled tank: %s"), *tank->GetName());
	}

}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("Tank Player Controller Tick."));
	//AimTowardsCrosshair
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	//Get world location if linetrace through crosshair
	//If it hits the lanscape
	  //Tell the controllled tank to aim at this point
}


