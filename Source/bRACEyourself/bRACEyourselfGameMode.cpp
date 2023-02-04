// Copyright Epic Games, Inc. All Rights Reserved.

#include "bRACEyourselfGameMode.h"
#include "bRACEyourselfPawn.h"
#include "bRACEyourselfHud.h"

AbRACEyourselfGameMode::AbRACEyourselfGameMode()
{
	DefaultPawnClass = AbRACEyourselfPawn::StaticClass();
	HUDClass = AbRACEyourselfHud::StaticClass();
}
