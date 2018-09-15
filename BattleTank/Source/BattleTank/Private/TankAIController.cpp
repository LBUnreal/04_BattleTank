// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	ATank* AIControlledTank = Cast<ATank>(GetPawn());
	ATank* PlayerControlledTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (!ensure(PlayerControlledTank && AIControlledTank)) { return; }
	
	//Move towards the player
	MoveToActor(PlayerControlledTank, AcceptanceRadius);

	//Aim Towards the player
	UTankAimingComponent* AimingComponent = AIControlledTank->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(AimingComponent)) { return; }
		
	AimingComponent->AimAt(PlayerControlledTank->GetActorLocation());
		
	AimingComponent->Fire(); //TODO don't fire every frame
	
}

