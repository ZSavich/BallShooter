// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Widgets/SPlayerWidget.h"
#include "SGameHUD.generated.h"
UCLASS()
class BALLSHOOTER_API ASGameHUD : public AHUD
{
	GENERATED_BODY()

    /** Player's Widget Pointer **/
    UPROPERTY()
    USPlayerWidget* PlayerWidget;
    
protected:
    /** The Class of the Player Widget that will be created in BeginPlay **/
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Widgets")
    TSubclassOf<USPlayerWidget> PlayerWidgetClass;

public:
    virtual void BeginPlay() override;
};
