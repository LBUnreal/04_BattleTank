// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATank::AimAt(FVector HitPosition) const
{
	//TankAimingComponent->AimAt(HitPosition, LaunchSpeed);
}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (Barrel && isReloaded)
	{
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
