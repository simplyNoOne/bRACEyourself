// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "CarInterface.h"
#include "CarMovementComponent.h"
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

	UFUNCTION(BlueprintCallable)
	float GetCarSpeed();

	UFUNCTION(BlueprintCallable)
	float GetCarRPM();

	UFUNCTION(BlueprintCallable)
	int32 GetCarGear();

	UFUNCTION(BlueprintCallable)
	float GetDistance();

	UFUNCTION(BlueprintCallable)
	float GetEnergyRatio();

	EEngineState GetEngineState();

	float GetMaxRPM();


	void UpdateDistance(float dT);

	void UpdateEnergy(float dT);



	UFUNCTION(BlueprintCallable)
	inline void SetDistance(float distance) { Distance = distance; }
	UFUNCTION(BlueprintCallable)
	inline void SetEnergy(float energy) { Energy = energy; }
	
};
