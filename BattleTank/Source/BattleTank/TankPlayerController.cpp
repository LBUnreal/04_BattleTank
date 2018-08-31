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
		//UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());
		//TODO;Tell the controlled tank to aim at this point
	}

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// Find the crosshair position
	int32 ViewportSizeX;
	int32 ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation =
		FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	// "De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	FVector ReticleWorldPosition;

	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-trace along that look direction, see what we hit (up to max range)
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
		UE_LOG(LogTemp, Warning, TEXT("Hit location is: %s"), *OutHitLocation.ToString());
	}

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const
{
	FVector WorldLocation;
	FVector WorldDirection;

	bool bDeprojectResult =
		DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, WorldDirection);

	if (bDeprojectResult)
	{
		OutLookDirection = WorldDirection;
	}

	return bDeprojectResult;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
	FHitResult HitResult;
	FVector StartPosition = PlayerCameraManager->GetCameraLocation();
	FVector EndPosition = LookDirection * LineTraceRange + StartPosition;
	
	//Line trace succeeds
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartPosition, EndPosition, ECollisionChannel::ECC_Visibility))
	{
		//Set hit location
		OutHitLocation = HitResult.Location;
		return true;
	}

	//Set the hit location to zero FVector if there is no target
	OutHitLocation = FVector(0);
	return false;
}
