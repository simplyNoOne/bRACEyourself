// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameMode.h"
#include "CustomGameState.h"
#include "Car.h"
#include "CustomPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Checkpoint.h"
#include "FinishLine.h"

ACustomGameMode::ACustomGameMode()
{
	GameStateClass = ACustomGameState::StaticClass();
	DefaultPawnClass = ACar::StaticClass();
	PlayerControllerClass = ACustomPlayerController::StaticClass();
	ElapsedSeconds = 0;

	bCountTime = false;
	bGamePaused = false;
	CheckpointsPassed = 0;
}

void ACustomGameMode::BeginPlay()
{
	Super::BeginPlay();


	
}

void ACustomGameMode::RestartGame_Implementation()
{

}



bool ACustomGameMode::LoadGame_Implementation()
{
	return false;
}

void ACustomGameMode::UpdateElapsed(float dT)
{
	if (bCountTime) {
		Time += dT;
		if (Time > 1.f) {
			Time = 0.f;
			ElapsedSeconds++;
		}
	}
}


void ACustomGameMode::StartGame_Implementation()
{
	GetWorld()->GetTimerManager().SetTimer(CountdownFinished, this, &ACustomGameMode::StartRace, CountdownTime, false);


	TArray<AActor*> Checkpoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACheckpoint::StaticClass(), Checkpoints);
	NumCheckpoints = Checkpoints.Num();

	for (int i = 0; i < Checkpoints.Num(); i++) {
		ACheckpoint* temp = Cast<ACheckpoint>(Checkpoints[i]);
		if (temp)
			temp->CheckpointCrossed.AddDynamic(this, &ACustomGameMode::OnCheckpointCrossed);

	}
	AActor* Finish = UGameplayStatics::GetActorOfClass(GetWorld(), AFinishLine::StaticClass());
	AFinishLine* temp = Cast<AFinishLine>(Finish);
	if (temp)
		temp->FinishLineCrossed.AddDynamic(this, &ACustomGameMode::OnFinishLineCrossed);

}

void ACustomGameMode::StartRace_Implementation()
{

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, TEXT("clias"));
	bCountTime = true;
}

void ACustomGameMode::PauseGame_Implementation() 
{
	bGamePaused = true;
	bCountTime = false;
}

void ACustomGameMode::ResumeGame_Implementation()
{
	bGamePaused = false;
	bCountTime = true;
}

void ACustomGameMode::FinishGame_Implementation()
{
	bCountTime = false;

	SaveGame(Cast<ACustomGameState>(GameState)->SaveCurrentTime(ElapsedSeconds));
}

void ACustomGameMode::LoseGame_Implementation()
{
}

void ACustomGameMode::QuitToMenu_Implementation()
{
	bGamePaused = false;
}


void ACustomGameMode::SaveGame_Implementation(bool UpdateGhost)
{
}



void ACustomGameMode::OnCheckpointCrossed()
{
	CheckpointsPassed++;
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("lkahsikjsh"));
}

void ACustomGameMode::OnFinishLineCrossed()
{

	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, TEXT("lkahsikjsh"));
	if (NumCheckpoints == CheckpointsPassed)
		FinishGame();
}