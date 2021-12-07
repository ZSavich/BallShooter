// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/SPlayerWidget.h"

#include "SGameMode.h"
#include "SPlayerState.h"
#include "Components/TextBlock.h"

// Creates the Player Widget and adds it to the player viewport
void USPlayerWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    if(!GetWorld()) return;

    GameMode = GetWorld()->GetAuthGameMode<ASGameMode>();
    if(!GameMode) return;

    // Assign delegates
    GameMode->OnTargetKilled.AddUObject(this, &USPlayerWidget::OnTargetKilledHandle);
    GameMode->OnWaveFinished.AddDynamic(this, &USPlayerWidget::OnWaveFinished);

    // First update for scores
    OnTargetKilledHandle(nullptr);
    OnWaveFinished();
}

// Gets the Kill's Score and updates the Player HUD
void USPlayerWidget::OnTargetKilledHandle(const AActor* Victim)
{
    const auto PlayerState = GetOwningPlayer()->GetPlayerState<ASPlayerState>();
    if(!ensure(PlayerState)) return;

    const FText KillsScore = FText::AsNumber(PlayerState->GetKillsScore());
    
    KillsScoreText->SetText(KillsScore);
}

// Gets the Wave's Score and updates the Player HUD
void USPlayerWidget::OnWaveFinished()
{
    if(!ensure(GameMode)) return;
    const auto WavesScore = FText::AsNumber(GameMode->GetWavesScore());

    WavesScoreText->SetText(WavesScore);
}