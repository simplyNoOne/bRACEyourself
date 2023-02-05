// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "CarMovementComponent.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EEngineState : uint8{
	EES_Forward UMETA(DisplayName = "Forward"),
	EES_Reverse UMETA(DisplayName = "Reverse"),
	EES_Off UMETA(DisplayName = "Off"),
	EES_Failure UMETA(DisplayName = "Failure"),

	EES_MAX UMETA(DisplayName = "Default")
};

UCLASS()
class BRACEYOURSELF_API UCarMovementComponent : public UChaosWheeledVehicleMovementComponent
{
	GENERATED_BODY()
public:
	EEngineState EngineState;
	

private:
	FTimerHandle GearChangeTimerHandle;
	FTimerHandle EngineRestartTimerHandle;

	int32 tempGear;
	bool bGearChanging;

public:
	UCarMovementComponent();
	

	void MoveForward(float Val);
	void MoveRight(float Val);

	void GearUp();
	void GearDown();
	void ChangeGearBy(int32 value);
	void AfterGearChange();

	void HandbrakeOn();
	void HandbrakeOff();

	void RestartEngine();
	
};
