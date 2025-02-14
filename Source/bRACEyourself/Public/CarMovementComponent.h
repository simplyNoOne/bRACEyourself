// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "CarMovementComponent.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEngineFailure);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEngineOn);


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEngineOff);

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

	UPROPERTY(EditAnywhere, Category = "Car")
	float EnergyConsumptionMultiplier;

	UPROPERTY()
	FEngineFailure EngineFailure;

	UPROPERTY()
	FEngineOn EngineOn;

	UPROPERTY()
	FEngineOff EngineOff;

private:
	FTimerHandle GearChangeTimerHandle;
	FTimerHandle EngineRestartTimerHandle;

	int32 tempGear;
	bool bGearChanging;
	float EnergyConsumption;

public:
	UCarMovementComponent();
	

	void MoveForward(float Val);

	void GearUp();
	void GearDown();
	void ChangeGearBy(int32 value);
	void AfterGearChange();

	void RestartEngine();
	void OnEngineFailure();
	void OnEngineOff();

	bool ShouldIgnoreRPMDrop();

	inline float GetEnergyConsumption() { return EnergyConsumption; }

	void SetThrottleInput(float Throttle);
	

	
};
