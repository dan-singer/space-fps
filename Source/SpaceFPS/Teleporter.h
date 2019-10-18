// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Teleporter.generated.h"

UCLASS()
class SPACEFPS_API ATeleporter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATeleporter();

protected:
	UPROPERTY(EditAnywhere)
	ATeleporter* Link;

	UPROPERTY(EditAnywhere)
	bool MatchRotation = true;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void Teleport(AActor* teleportTarget);

	UFUNCTION(BlueprintCallable)
	void EndTeleport();

public:	
	bool Receiving = false;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
