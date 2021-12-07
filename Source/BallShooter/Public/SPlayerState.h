// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"


UCLASS()
class BALLSHOOTER_API ASPlayerState : public APlayerState
{
	GENERATED_BODY()

    int32 CountOfKills;

public:
    UFUNCTION(BlueprintCallable)
    int32 GetCountOfKills() const {return CountOfKills;}
};
