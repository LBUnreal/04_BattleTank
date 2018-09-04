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

	//No need to protect points as added at construction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitPosition) const
{
	TankAimingComponent->AimAt(HitPosition, LaunchSpeed);
}

void ATank::Fire()
{


	if (!Barrel) { return; }

	//Spawn a projectile at the socket location of the barrel
	FVector ProjectileLocation = Barrel->GetSocketLocation(FName("Projectile"));
	FRotator ProjectileRotator = Barrel->GetSocketRotation(FName("Projectile"));

	AProjectile* Projectile = 
		GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint, 
			ProjectileLocation, 
			ProjectileRotator);

	Projectile->LaunchProjectile(LaunchSpeed);
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}