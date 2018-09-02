// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"


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
			ESuggestProjVelocityTraceOption::DoNotTrace);

	if (bHasSuggestedProjectileVelocity)
	{
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		
		MoveBarrelTowards(AimDirection);

		UE_LOG(LogTemp, Warning, TEXT("%s is Aiming at  %s"),*TankName, *AimDirection.ToString());
	}
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent * BarrelToSet)
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
	UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *DeltaRotator.ToString());

	//TODO Move the barrel the right amount this frame
	//TODO Given a max elevation speed, and the frame time
}

