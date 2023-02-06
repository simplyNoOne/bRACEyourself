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

	bGamePaused = false;
}

void ACustomGameMode::BeginPlay()
{
	StartCountdown.Broadcast();
}

void ACustomGameMode::PauseGame_Implementation() 
{
	bGamePaused = true;
}

void ACustomGameMode::ResumeGame_Implementation()
{
	bGamePaused = false;
}

void ACustomGameMode::QuitToMenu_Implementation()
{
	bGamePaused = false;
}
