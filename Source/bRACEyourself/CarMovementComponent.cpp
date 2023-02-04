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

	TransmissionSetup.bUseAutomaticGears = false;
	TransmissionSetup.bUseAutoReverse = false;
	TransmissionSetup.GearChangeTime = 0.3f;
	bReverseAsBrake = false;
	
}

void UCarMovementComponent::MoveForward(float Val)
{
	if (EngineState != EEngineState::EES_Failure && EngineState != EEngineState::EES_Off) {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 0.05f, FColor::Yellow, UEnum::GetValueAsString(EngineState));
			GEngine->AddOnScreenDebugMessage(-1, 0.05f, FColor::Orange, FString::FromInt(GetTargetGear()));
			GEngine->AddOnScreenDebugMessage(-1, 0.05f, FColor::Red, FString::FromInt(GetEngineRotationSpeed()));
		}
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
			if (GetEngineRotationSpeed() > 4000.f && GetTargetGear() != 6) {
				if (GEngine)
					GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, TEXT("BOOOOM"));
				EngineState = EEngineState::EES_Failure;
				SetThrottleInput(0.f);
			}
			if (GetEngineRotationSpeed() < 1200.f && GetTargetGear() > 1 && !VehicleState.bVehicleInAir) {
				if (GEngine)
					GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, TEXT("MEH"));
				SetThrottleInput(0.f);
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

void UCarMovementComponent::GearDown()
{
	if (EngineState != EEngineState::EES_Failure && EngineState != EEngineState::EES_Off) {
		if (GetTargetGear() > 1) {
			ChangeGearBy(-1);
		}
		else if (GetTargetGear() == 1 ) {
			EngineState = EEngineState::EES_Reverse;
			ChangeGearBy(-2);
		}
		else if (GetTargetGear() == 0) {
			EngineState = EEngineState::EES_Reverse;
			ChangeGearBy(-1);
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
	SetTargetGear(0, true);
	EngineState = EEngineState::EES_Forward;
	GetWorld()->GetTimerManager().ClearTimer(EngineRestartTimerHandle);
}


