// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "CarSave.generated.h"

/**
 * 
 */
UCLASS()
class BRACEYOURSELF_API UCarSave : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "Framework")
	TArray<FTransform> GhostTrace;
	UPROPERTY(BlueprintReadWrite, Category = "Framework")
	TArray<int32> BestTimes;
	
};
