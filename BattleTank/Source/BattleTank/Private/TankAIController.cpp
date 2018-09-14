// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	ATank* AIControlledTank = Cast<ATank>(GetPawn());
	ATank* PlayerControlledTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (ensure(PlayerControlledTank))
	{
		//Move towards the player
		MoveToActor(PlayerControlledTank, AcceptanceRadius);

		//Aim Towards the player
		AIControlledTank->AimAt(PlayerControlledTank->GetActorLocation());

		AIControlledTank->Fire(); //TODO don't fire every frame
	}
}

