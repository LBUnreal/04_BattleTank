// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"


void UTankTurret::Rotate(float RelativeMovement)
{
	//We want to cap how fast the turret rotates
	RelativeMovement = FMath::Clamp<float>(RelativeMovement, -1.0F, 1.0F); //these max/min values can be UPROPERTY

	float RotationChange = RelativeMovement * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float RawNewRotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0, RawNewRotation, 0));
}

