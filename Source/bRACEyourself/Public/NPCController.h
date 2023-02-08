// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NPCController.generated.h"

class USplineComponent;
class ASpline;

/**
 * 
 */
UCLASS()
class BRACEYOURSELF_API ANPCController : public AAIController
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, Category = "NPCs")
	USplineComponent* PathToFollow;

public:
	void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "NPCs")
	void WalkPath(float Duration);

	void UpdatePath(ASpline* Path);
	
};
