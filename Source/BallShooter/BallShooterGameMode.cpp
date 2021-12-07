// Copyright Epic Games, Inc. All Rights Reserved.

#include "BallShooterGameMode.h"
#include "BallShooterHUD.h"
#include "BallShooterCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABallShooterGameMode::ABallShooterGameMode()
	: Super()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	HUDClass = ABallShooterHUD::StaticClass();
}
