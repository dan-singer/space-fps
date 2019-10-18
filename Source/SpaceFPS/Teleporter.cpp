// Fill out your copyright notice in the Description page of Project Settings.


#include "Teleporter.h"
#include <GameFramework/Character.h>
#include <GameFramework/PawnMovementComponent.h>

// Sets default values
ATeleporter::ATeleporter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATeleporter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATeleporter::Teleport(AActor* teleportTarget)
{
	if (Receiving) {
		return;
	}
	Link->Receiving = true;
	if (MatchRotation) {
		ACharacter* character = Cast<ACharacter>(teleportTarget);
		if (character) {
			character->GetMovementComponent()->StopMovementImmediately();
			character->GetController()->SetControlRotation(Link->GetActorRotation());
		} 
		else {
			teleportTarget->SetActorRotation(Link->GetActorRotation());
		}
	}
	teleportTarget->SetActorLocation(Link->GetActorLocation());

}

void ATeleporter::EndTeleport()
{
	Receiving = false;
}

// Called every frame
void ATeleporter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

