// Fill out your copyright notice in the Description page of Project Settings.


#include "CarBackWheel.h"

UCarBackWheel::UCarBackWheel() {
	AxleType = EAxleType::Rear;
	WheelRadius = 40.f;
	WheelWidth = 45.f;

	bAffectedByEngine = true;
	bAffectedByHandbrake = true;
	bAffectedBySteering = false;
}