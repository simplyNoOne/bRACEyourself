// Fill out your copyright notice in the Description page of Project Settings.


#include "CarMovementComponent.h"
#include "CarBackWheel.h"
#include "CarFrontWheel.h"

UCarMovementComponent::UCarMovementComponent()
{
	EngineState = EEngineState::EES_Forward;

	WheelSetups.SetNum(4);
	WheelSetups[0].WheelClass = UCarFrontWheel::StaticClass();
	WheelSetups[1].WheelClass = UCarFrontWheel::StaticClass();

	WheelSetups[2].WheelClass = UCarBackWheel::StaticClass();
	WheelSetups[3].WheelClass = UCarBackWheel::StaticClass();

	bReverseAsBrake = false;

	EngineSetup.MaxRPM = 7500.f;
	EngineSetup.EngineIdleRPM = 1000.f;

	TransmissionSetup.bUseAutomaticGears = false;
	TransmissionSetup.bUseAutoReverse = false;
	TransmissionSetup.GearChangeTime = 0.3f;

	TransmissionSetup.FinalRatio = 0.6f;
	TransmissionSetup.ForwardGearRatios.SetNum(6);
	TransmissionSetup.ForwardGearRatios[0] = 45.f;
	TransmissionSetup.ForwardGearRatios[1] = 35.f;
	TransmissionSetup.ForwardGearRatios[2] = 25.f;
	TransmissionSetup.ForwardGearRatios[3] = 15.f;
	TransmissionSetup.ForwardGearRatios[4] = 7.f;
	TransmissionSetup.ForwardGearRatios[5] = 4.f;
	
}

void UCarMovementComponent::MoveForward(float Val)
{
	if (EngineState != EEngineState::EES_Failure && EngineState != EEngineState::EES_Off) {
		if (!bGearChanging) {
			if (Val >= 0.f) {
				if (EngineState == EEngineState::EES_Forward) {
					SetThrottleInput(Val);
					SetBrakeInput(0.f);
				}
				if (EngineState == EEngineState::EES_Reverse) {
					SetBrakeInput(0.f);
					SetThrottleInput(Val * 0.7);
				}
			}
			if (Val < 0.f) {
				SetThrottleInput(0.f);
				SetBrakeInput(-Val);
			}
			if (GetEngineRotationSpeed() > (GetEngineMaxRotationSpeed() - 500.f) && GetTargetGear() != 6) {
				if (GEngine)
					GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, TEXT("BOOOOM"));
				EngineState = EEngineState::EES_Failure;
				SetThrottleInput(0.f);
			}
			if (GetEngineRotationSpeed() < 1200.f && GetTargetGear() > 1 && !VehicleState.bVehicleInAir) {
				if (GEngine)
					GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, TEXT("MEH"));
				SetThrottleInput(0.f);
				SetTargetGear(0, true);
				EngineState = EEngineState::EES_Off;
				GetWorld()->GetTimerManager().SetTimer(EngineRestartTimerHandle, this, &UCarMovementComponent::RestartEngine, 3.f, false);
			}
		}
	}
}

void UCarMovementComponent::MoveRight(float Val)
{
	SetSteeringInput(Val);
}

void UCarMovementComponent::GearUp()
{
	if (bGearChanging) {
		if (tempGear != -1)
			tempGear += 1;
		else
			tempGear += 2;
	}
	else {
		if (EngineState != EEngineState::EES_Failure && EngineState != EEngineState::EES_Off) {
			if (GetTargetGear() < 6) {
				if (EngineState == EEngineState::EES_Reverse) {
					EngineState = EEngineState::EES_Forward;
					ChangeGearBy(2);
				}
				else {
					ChangeGearBy(1);
				}
			}
		}
	}
}

void UCarMovementComponent::GearDown()
{
	if (bGearChanging) {
		if (tempGear != 1)
			tempGear -= 1;
		else
			tempGear -= 2;
	}
	else {
		if (EngineState != EEngineState::EES_Failure && EngineState != EEngineState::EES_Off) {
			if (GetTargetGear() > 1) {
				ChangeGearBy(-1);
			}
			else if (GetTargetGear() == 1) {
				EngineState = EEngineState::EES_Reverse;
				ChangeGearBy(-2);
			}
			else if (GetTargetGear() == 0) {
				EngineState = EEngineState::EES_Reverse;
				ChangeGearBy(-1);
			}
		}
	}
}

void UCarMovementComponent::ChangeGearBy(int32 value) 
{
	bGearChanging = true;
	tempGear = GetTargetGear() + value;
	SetTargetGear(0, true);
	SetThrottleInput(0.f);
	GetWorld()->GetTimerManager().SetTimer(GearChangeTimerHandle, this, &UCarMovementComponent::AfterGearChange, 0.5f, false);

}

void UCarMovementComponent::AfterGearChange()
{
	SetTargetGear(tempGear, true);
	GetWorld()->GetTimerManager().ClearTimer(GearChangeTimerHandle);
	bGearChanging = false;
}





void UCarMovementComponent::HandbrakeOn()
{
	SetHandbrakeInput(false);
}

void UCarMovementComponent::HandbrakeOff()
{
	SetHandbrakeInput(false);
}

void UCarMovementComponent::RestartEngine()
{
	
	EngineState = EEngineState::EES_Forward;
	GetWorld()->GetTimerManager().ClearTimer(EngineRestartTimerHandle);
}


