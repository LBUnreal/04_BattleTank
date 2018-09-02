// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float DegreesPerSecond);
	
private:

	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreesPerSecond = 20.0F; //Sensible default
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxElevationInDegrees = 40.0F; //Sensible default; does not look awkward, nor clips through the tank
	UPROPERTY(EditAnywhere, Category = Setup)
		float MinElevationInDegrees = -0.0F;
};
