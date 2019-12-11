// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceFPSGameInstance.h"

USpaceFPSGameInstance::USpaceFPSGameInstance() : UGameInstance()
{
	Rooms.Add("Mini Boss", { 5, 0 });
	Rooms.Add("Final Boss", { 6, 0 });
}

void USpaceFPSGameInstance::ReportEnemyKilled(FString roomName)
{
	if (roomName == "") {
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Enemy killed"));
	Rooms[roomName].EnemiesKilled++;
	if (Rooms[roomName].EnemiesKilled >= Rooms[roomName].TotalEnemies) {
		RoomCleared.Broadcast(roomName);
	}
}

