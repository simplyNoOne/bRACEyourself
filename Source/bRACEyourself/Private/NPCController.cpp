// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCController.h"
#include "NPC.h"
#include "Components/SplineComponent.h"
#include "Spline.h"

void ANPCController::BeginPlay()
{
	Super::BeginPlay();

	ANPC* NPC = Cast<ANPC>(GetPawn());
	if (NPC) 
		PathToFollow = NPC->Path->SplinePath;
}

void ANPCController::WalkPath_Implementation()
{
}
