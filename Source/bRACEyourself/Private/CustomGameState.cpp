// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameState.h"

ACustomGameState::ACustomGameState()
{
	NumberOfScores = 8;
}

bool ACustomGameState::SaveCurrentTime(int32 time)
{
	LastTime = time;
	Times.Add(time);
	Times.Sort();
	if (Times.Num() > NumberOfScores)
		Times.RemoveAt(NumberOfScores);
	if (LastTime == Times[0]) {
		return true;
	}
	return false;
}
