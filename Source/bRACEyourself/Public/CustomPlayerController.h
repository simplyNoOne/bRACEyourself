// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CustomPlayerController.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateSpeed, float, speed);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateRPM, float, rpm);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateGear, int32, gear);
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

public:
	void Tick(float deltaTime) override;

	void Update(float dT);
	
};
