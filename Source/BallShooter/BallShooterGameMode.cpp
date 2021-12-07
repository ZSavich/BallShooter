// Copyright Epic Games, Inc. All Rights Reserved.

#include "BallShooterGameMode.h"
#include "BallShooterHUD.h"
#include "BallShooterCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABallShooterGameMode::ABallShooterGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ABallShooterHUD::StaticClass();
}
