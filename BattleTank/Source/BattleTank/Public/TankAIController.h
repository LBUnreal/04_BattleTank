// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Tank.h"
#include "Engine/World.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	ATank * GetAIControlledTank() const;
	ATank* GetPlayerControlledTank() const;
public:
	void BeginPlay() override;
	
	
};
