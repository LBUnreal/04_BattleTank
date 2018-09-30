// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Classes/Particles/ParticleSystemComponent.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/PhysicsEngine/RadialForceComponent.h"
#include "Projectile.generated.h"

//Foward Declarations
class UProjectileMovementComponent;

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	void LaunchProjectile(float Speed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* CollisionMesh = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UParticleSystemComponent* LaunchBlast = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UParticleSystemComponent* ImpactBlast = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		URadialForceComponent* ExplosionForce = nullptr;
private:
	UProjectileMovementComponent * ProjectileMovement = nullptr;
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
