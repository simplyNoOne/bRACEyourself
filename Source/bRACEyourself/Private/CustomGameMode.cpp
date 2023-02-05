// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameMode.h"
#include "CustomGameState.h"
#include "Car.h"
#include "CustomPlayerController.h"

ACustomGameMode::ACustomGameMode()
{
	GameStateClass = ACustomGameState::StaticClass();
	DefaultPawnClass = ACar::StaticClass();
	PlayerControllerClass = ACustomPlayerController::StaticClass();
}

void ACustomGameMode::BeginPlay()
{
	StartCountdown.Broadcast();
}
