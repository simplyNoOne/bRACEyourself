// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CustomGameState.generated.h"

/**
 * 
 */

UCLASS()
class BRACEYOURSELF_API ACustomGameState : public AGameStateBase
{
	GENERATED_BODY()

public:


	UPROPERTY(BlueprintReadWrite, Category = "Framework")
	TArray<int32> Times;

	UPROPERTY(BlueprintReadOnly, Category = "Framework")
	int32 NumberOfScores;

private:
	
	float LastTime;


public:
	ACustomGameState();

	bool SaveCurrentTime(int32 time);

	
};
