// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"
#include <Components/ActorComponent.h>

// Sets default values for this component's properties
UMovingPlatform::UMovingPlatform()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	Center = GetOwner()->GetActorLocation();
}


// Called every frame
void UMovingPlatform::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FVector target, start;
	if (Step == 0) {
		start = Center;
		target = Center + Extents;
	}
	else if (Step == 1) {
		start = Center + Extents;
		target = Center;
	}
	else if (Step == 2) {
		start = Center;
		target = Center - Extents;
	}
	else {
		start = Center - Extents;
		target = Center;
	}

	FVector finalLoc = FMath::Lerp(start, target, StepTimer / StepDuration);
	GetOwner()->SetActorLocation(finalLoc);
	StepTimer += DeltaTime;

	if (StepTimer >= StepDuration) {
		++Step;
		Step %= 4;
		StepTimer = 0.0f;
	}
}

