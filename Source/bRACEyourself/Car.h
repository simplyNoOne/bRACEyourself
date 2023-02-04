// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "Car.generated.h"



class UCameraComponent;
class USpringArmComponent;
class UCarMovementComponent;
/**
 * 
 */
UCLASS()
class BRACEYOURSELF_API ACar : public AWheeledVehiclePawn
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

public:
	ACar();

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	
};
