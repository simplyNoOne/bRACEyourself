// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CustomGameMode.generated.h"

/**
* 
*/

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGhostLoaded);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGhostNotLoaded);

UCLASS()
class BRACEYOURSELF_API ACustomGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Framework")
	int32 CountdownTime;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Framework")
	int32 ElapsedSeconds;

	UPROPERTY( BlueprintCallable, BlueprintAssignable, Category = "Ghost")
	FGhostLoaded GhostLoaded;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Ghost")
	FGhostNotLoaded GhostNotLoaded;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Ghost")
	TArray<FTransform> GhostReplay;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Ghost")
	TArray<FTransform> GhostRecord;

private:

	FTimerHandle CountdownFinished;

	bool bCountTime;

	bool bGamePaused;

	float Time;

	int32 CheckpointsPassed;

	int32 NumCheckpoints;

	bool bFinishCrossed;

	


public:

	ACustomGameMode();

	void BeginPlay() override;

	inline bool IsGamePaused() { return bGamePaused; }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Framework")
	void StartGame();

	UFUNCTION(BlueprintNativeEvent, Category = "Framework")
	void StartRace();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Framework")
	void RestartGame();

	UFUNCTION(BlueprintNativeEvent, Category = "Framework")
	void PauseGame();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Framework")
	void ResumeGame();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Framework")
	void FinishGame();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Framework")
	void LoseGame();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Framework")
	void QuitToMenu();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Framework")
	void SaveGame(bool UpdateGhost);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Framework")
	void LoadGame();

	UFUNCTION()
	void UpdateElapsed(float dT);

	UFUNCTION()
	void OnCheckpointCrossed();

	UFUNCTION()
	void OnFinishLineCrossed();

	
	
};
