// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	ATank * GetControlledTank() const;
	void Tick(float DeltaTime) override;
	//Start the tank moving towards the barrel so that a shot would be where the 
	//crosshair intersects the world
	void AimTowardsCrosshair(); 
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
public:
	void BeginPlay() override;


};
