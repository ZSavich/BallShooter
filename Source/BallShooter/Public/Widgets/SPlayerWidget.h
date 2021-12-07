// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SPlayerWidget.generated.h"

class UTextBlock;
class ASGameMode;

UCLASS()
class BALLSHOOTER_API USPlayerWidget : public UUserWidget
{
    GENERATED_BODY()
    
protected:
    // Called when the game starts
    virtual void NativeOnInitialized() override;
    
    // Text Block with Kill's Score information
    UPROPERTY(meta = (BindWidget))
    UTextBlock* KillsScoreText;

    // Text Block with Wave's Score information
    UPROPERTY(meta = (BindWidget))
    UTextBlock* WavesScoreText;

    // Pointer for Game Mode
    UPROPERTY()
    ASGameMode* GameMode;

    // Handle for FOnTargetKilled multicast Delegate
    void OnTargetKilledHandle(const AActor* Victim);
    // Handle for FOnWaveFinished dynamic Delegate
    UFUNCTION()
	void OnWaveFinished();
};
