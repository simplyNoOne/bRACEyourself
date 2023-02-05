// Fill out your copyright notice in the Description page of Project Settings.


#include "CarFrontWheel.h"

UCarFrontWheel::UCarFrontWheel()
{
	AxleType = EAxleType::Front;
	WheelRadius = 40.f;
	WheelWidth = 40.f;

	MaxSteerAngle = 45.f;
	bAffectedByEngine = true;
	bAffectedByHandbrake = true;
	bAffectedBySteering = true;

	FrictionForceMultiplier = 3.5f;
	
}
