// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0F, 1.0F);
	//TODO Move the barrel the right amount this frame
	//TODO Given a max elevation speed, and the frame time
	float ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	SetRelativeRotation(
		FRotator(
			FMath::Clamp(RawNewElevation, MinElevationInDegrees, MaxElevationInDegrees),
			0.0f,
			0.0f));

}

