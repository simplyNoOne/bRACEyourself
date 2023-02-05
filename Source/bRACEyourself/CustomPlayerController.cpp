// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPlayerController.h"
#include "Public/CarInterface.h"
#include "Car.h"

void ACustomPlayerController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	Update(deltaTime);


	if (GetPawn()->Implements<UCarInterface>()) {
		//check if failure, if so, pass maxrpm, if off, pass 0rpm
		UpdateSpeed.Broadcast(ICarInterface::Execute_GetCarSpeed(GetPawn()));
		UpdateRPM.Broadcast(ICarInterface::Execute_GetCarRPM(GetPawn()));
		UpdateGear.Broadcast(ICarInterface::Execute_GetCarGear(GetPawn()));
	}
}

void ACustomPlayerController::Update(float dT) {
	Cast<ACar>(GetPawn())->UpdateDistance(dT);
}
