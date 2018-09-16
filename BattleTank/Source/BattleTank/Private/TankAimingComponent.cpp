// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay()
{
	//So that first fire is after initial reload
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if ((FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds)
	{
		FiringStatus = EFiringStatus::Reloading;
	}
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }
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
	}

}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	//rotate the turret towards the reticle until the turret is underneath it 
	//elevate the barrel up until it can fire a projectile the distance to the target that it is aiming at
	if (!ensure(Barrel) || !ensure(Turret)) { return; }

	//Work-out the difference between current barrel rotation, and AimDirection
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;

	//Can the DeltaRotator.Yaw be used for the Turret? Yes this can be used for the Turret->Rotate
	Turret->Rotate(DeltaRotator.Yaw);
	Barrel->Elevate(DeltaRotator.Pitch); 
}


void UTankAimingComponent::Fire()
{
	if (FiringStatus != EFiringStatus::Reloading)
	{
		if (!ensure(Barrel)) { return; }
	    if (!ensure(ProjectileBlueprint)) { return; }

		//Spawn a projectile at the socket location of the barrel
		FVector ProjectileLocation = Barrel->GetSocketLocation(FName("Projectile"));
		FRotator ProjectileRotator = Barrel->GetSocketRotation(FName("Projectile"));

		AProjectile* Projectile =
			GetWorld()->SpawnActor<AProjectile>(
				ProjectileBlueprint,
				ProjectileLocation,
				ProjectileRotator);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}


