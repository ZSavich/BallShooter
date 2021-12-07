// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"


UCLASS()
class BALLSHOOTER_API ASPlayerState : public APlayerState
{
	GENERATED_BODY()

    // Score of killed targets
    int32 KillsScore = 0;

public:
    // Getter for privat properties 
    UFUNCTION(BlueprintCallable)
    int32 GetKillsScore() const {return KillsScore;}

    // Increase KillsScore by one
    FORCEINLINE void IncreaseKillsScore() {++KillsScore;}
};
