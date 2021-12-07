// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BALLSHOOTER_API ASPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
    
    
public:

    virtual void OnPossess(APawn* InPawn) override;
};
