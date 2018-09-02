// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/World.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

//Forward Declarations
class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		float CrossHairXLocation = 0.5;
	UPROPERTY(EditAnywhere)
		float CrossHairYLocation = 0.33333;
	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000;

	ATank * GetControlledTank() const;
	void Tick(float DeltaTime) override;
	//Start the tank moving towards the barrel so that a shot would be where the 
	//crosshair intersects the world
	void AimTowardsCrosshair(); 
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitResult) const;

public:
	void BeginPlay() override;


};
