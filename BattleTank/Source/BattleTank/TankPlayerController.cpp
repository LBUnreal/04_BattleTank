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
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // Out Parameter

	if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());
		//TODO;Tell the controlled tank to aim at this point
	}

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	//TODO; remove temporary assignment of OutHitLocation
	OutHitLocation = FVector(1.0); //Assigns this a value of {1.0F, 1.0F, 1.0F}

	//raycast through the dot to anything in the terrain

	//if we hit anything
		//Set the OutHitLocation to the location that was hit with the raycast
		//return true
	//else
		//return false
	return false;
}


