// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPlayerController.h"
#include "CarInterface.h"
#include "Car.h"
#include "CarMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CustomGameMode.h"
#include "CustomGameState.h"

ACustomPlayerController::ACustomPlayerController()
{
}

void ACustomPlayerController::BeginPlay()
{
	CustomGM = Cast<ACustomGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (GetPawn()) {
		GetPawn()->InputComponent->BindAction("Pause", IE_Pressed, this, &ACustomPlayerController::PauseGame);
		GetPawn()->InputComponent->GetActionBinding(4).bExecuteWhenPaused = true;	//has to be for, fuck knows how those indices work
		Car = Cast<ACar>(GetPawn());
		
		Car->EnergyBoosted.AddDynamic(this, &ACustomPlayerController::EnergyBoost);
	}
}


void ACustomPlayerController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if (Car && CustomGM){
		Update(deltaTime);

		CustomGM->UpdateElapsed(deltaTime);
	
		//check if failure, if so, pass maxrpm, if off, pass 0rpm
		if (Car->GetEngineState() == EEngineState::EES_Off) {
			UpdateRPM.Broadcast(0.f);
			UpdateGear.Broadcast(0);
		}
		else if (Car->GetEngineState() == EEngineState::EES_Failure) {
			UpdateRPM.Broadcast(Car->GetMaxRPM());
			UpdateGear.Broadcast(-10);
		}
		else {
			UpdateRPM.Broadcast(Car->GetCarRPM());
			UpdateGear.Broadcast(Car->GetCarGear());
		}
		UpdateSpeed.Broadcast(Car->GetCarSpeed());
		UpdateTime.Broadcast(CustomGM->ElapsedSeconds);
		UpdateEnergy.Broadcast(Car->GetEnergyRatio());
	}
}

void ACustomPlayerController::Update(float dT) {
	
	Car->UpdateDistance(dT);
	Car->UpdateEnergy(dT);
	if (Car->GetEngineState() == EEngineState::EES_Failure) {
		if (Car->GetCarSpeed() < 1.f)
			CustomGM->LoseGame();
	}
	if (Car->GetEnergyRatio() == 0.f) {
		if (Car->GetCarSpeed() < 1.f)
			CustomGM->LoseGame();
	}

}

void ACustomPlayerController::PauseGame()
{
	
	if (CustomGM) {
		if (!CustomGM->IsGamePaused())
			CustomGM->PauseGame();
		else 
			CustomGM->ResumeGame();
	}
}

void ACustomPlayerController::EnergyBoost()
{
	UpdateEnergyBoosted.Broadcast();
}


