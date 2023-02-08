// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCController.h"
#include "NPC.h"
#include "Components/SplineComponent.h"
#include "Spline.h"

void ANPCController::BeginPlay()
{
	Super::BeginPlay();
}

void ANPCController::UpdatePath(ASpline* Path)
{
	 PathToFollow = Path->SplinePath; 
}


void ANPCController::WalkPath_Implementation(float Duration)
{
}
