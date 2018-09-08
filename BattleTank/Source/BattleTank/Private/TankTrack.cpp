// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	//float Time = GetWorld()->GetTimeSeconds();
	FString Track = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s throttle: %f"), *Track , Throttle);
}


