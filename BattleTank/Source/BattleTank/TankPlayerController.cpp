// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!GetPawn()) { return; }
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return;  }
	
    FoundAimingComponent(AimingComponent);

}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	FVector HitLocation; // Out Parameter

	if (GetSightRayHitLocation(HitLocation))
	{		
		AimingComponent->AimAt(HitLocation);
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
