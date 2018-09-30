// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/World.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//Forward declarations
class UTankBarrel; 


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	//Called by the engine when actor is dealt
	float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController* EventInstigator, AActor* Damagecauser) override;

	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
		 int32 CurrentHealth = StartingHealth;
};
