// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SpaceFPSGameInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRoomCleared, FString, RoomName);

struct Room {
	int TotalEnemies = 0;
	int EnemiesKilled = 0;
};

/**
 * 
 */
UCLASS()
class SPACEFPS_API USpaceFPSGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:
	TMap<FString, Room> Rooms;
protected:
	UPROPERTY(BlueprintAssignable)
	FRoomCleared RoomCleared;
public:
	USpaceFPSGameInstance();

	void ReportEnemyKilled(FString roomName);
	
};
