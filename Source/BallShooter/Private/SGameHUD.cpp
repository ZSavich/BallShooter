// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameHUD.h"

void ASGameHUD::BeginPlay()
{
    Super::BeginPlay();
    if(!ensure(PlayerWidgetClass)) return;

    // Creates Player's Widget that shows the scores
    PlayerWidget = CreateWidget<USPlayerWidget>(GetWorld(), PlayerWidgetClass);
    PlayerWidget->AddToViewport();
}
