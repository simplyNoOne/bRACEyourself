// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CustomGameMode.generated.h"

/**
* 
*/

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartCountdown);

 
UCLASS()
class BRACEYOURSELF_API ACustomGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "CustomEvents")
	FStartCountdown StartCountdown;

	ACustomGameMode();

	void BeginPlay() override;
	
};
