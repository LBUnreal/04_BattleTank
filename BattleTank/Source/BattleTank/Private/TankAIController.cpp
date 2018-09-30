// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h" //So we can implement on Death

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	APawn* AIControlledTank = GetPawn();
	APawn* PlayerControlledTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!ensure(PlayerControlledTank && AIControlledTank)) { return; }
	
	//Move towards the player
	MoveToActor(PlayerControlledTank, AcceptanceRadius);

	//Aim Towards the player
	UTankAimingComponent* AimingComponent = AIControlledTank->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(AimingComponent)) { return; }
		
	AimingComponent->AimAt(PlayerControlledTank->GetActorLocation());
	
	if (AimingComponent->GetFiringStatus() == EFiringStatus::Locked)
	{
		AimingComponent->Fire(); //TODO don't fire every frame
	}
	
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		//Note: Doing this here because the constructor is too early and 
		//BeginPlay might cause a race condition
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::OnPossessedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Tank died"));
}
