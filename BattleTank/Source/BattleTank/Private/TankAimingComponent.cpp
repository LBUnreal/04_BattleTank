// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAimingComponent.h"
#include "TankBarrel.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}



void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }
	FVector OutLaunchVelocity;


	FString TankName = GetOwner()->GetName();
	FVector BarrelLocation = Barrel->GetSocketLocation(FName("Projectile"));

	//Calculate the OutLaunchVelocity
	bool bHasSuggestedProjectileVelocity =
		UGameplayStatics::SuggestProjectileVelocity(
			this,
			OutLaunchVelocity,
			BarrelLocation,
			HitLocation,
			LaunchSpeed,
			false,
			0, 
			0,
			ESuggestProjVelocityTraceOption::DoNotTrace); //Note: optional parameters don't work; always specify values

	if (bHasSuggestedProjectileVelocity) 
	{
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		
		MoveBarrelTowards(AimDirection);

		float Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: %s: Suggested Projectile Velocity found"), Time, *TankName);
	}
	else
	{
		float Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: %s: Suggested Projectile Velocity not found"), Time, *TankName);
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}

//TODO add SetTurretReference

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	//rotate the turret towards the reticle until the turret is underneath it 
	//elevate the barrel up until it can fire a projectile the distance to the target that it is aiming at

	//Work-out the difference between current barrel rotation, and AimDirection
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;


	Barrel->Elevate(DeltaRotator.Pitch); 
}

