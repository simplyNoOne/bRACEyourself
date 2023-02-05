// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "Public/CarInterface.h"
#include "Car.generated.h"



class UCameraComponent;
class USpringArmComponent;
class UCarMovementComponent;

/**
 * 
 */
UCLASS()
class BRACEYOURSELF_API ACar : public AWheeledVehiclePawn, public ICarInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	UCarMovementComponent* MovementComponent;

	UPROPERTY(Category = "Camera", VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	/** Camera component that will be our viewpoint */
	UPROPERTY(Category = "Camera", VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;
	
private:
	float Distance;
	float Energy;
	float MaxEnergy;

public:
	ACar();

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	UFUNCTION(BlueprintNativeEvent)
	float GetCarSpeed();

	UFUNCTION(BlueprintNativeEvent)
	float GetCarRPM();

	UFUNCTION(BlueprintNativeEvent)
	int32 GetCarGear();

	void UpdateDistance(float dT);


	inline void SetDistance(float distance) { Distance = distance; }
	inline void SetEnergy(float energy) { Energy = energy; }

	inline float GetDistance() { return Distance; }
	inline float GetEnergyRatio() { return Energy / MaxEnergy; }
	
};
