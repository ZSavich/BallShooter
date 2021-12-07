// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SPlayerController.h"

#include "SGameHUD.h"

void ASPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    
    const auto HUD = GetHUD<ASGameHUD>();
    if(!ensure(HUD)) return;
}
