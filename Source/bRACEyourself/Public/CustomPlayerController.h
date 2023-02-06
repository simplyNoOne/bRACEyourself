// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CustomPlayerController.generated.h"

class ACar;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateSpeed, float, speed);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateRPM, float, rpm);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateGear, int32, gear);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateDistance, float, distance);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateEnergy, float, energy);
/**
 * 
 */
UCLASS()
class BRACEYOURSELF_API ACustomPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, Category = "HUD")
	FUpdateSpeed UpdateSpeed;

	UPROPERTY(BlueprintAssignable, Category = "HUD")
	FUpdateRPM UpdateRPM;

	UPROPERTY(BlueprintAssignable, Category = "HUD")
	FUpdateGear UpdateGear;

	UPROPERTY(BlueprintAssignable, Category = "HUD")
	FUpdateDistance UpdateDistance;

	UPROPERTY(BlueprintAssignable, Category = "HUD")
	FUpdateEnergy UpdateEnergy;

private:
	ACar* Car;

public:

	ACustomPlayerController();

	void BeginPlay();

	void Tick(float deltaTime) override;

	void Update(float dT);

	void PauseGame();
	
};
