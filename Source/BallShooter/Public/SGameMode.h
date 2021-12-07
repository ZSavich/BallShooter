// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SGameMode.generated.h"

class ASTargetSphere;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnTargetKilled, const AActor* Victim);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWaveFinished);

UCLASS()
class BALLSHOOTER_API ASGameMode : public AGameModeBase
{
	GENERATED_BODY()

    UPROPERTY()
    TArray<AActor*> TargetInstances;
    FVector PlayerLocation;
    int32 KillsCount;
    int32 WavesCount;
    float MaxTargetSize;

    
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Wave")
    TSubclassOf<ASTargetSphere> TargetSphereClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Wave", meta = (ClampMin=10, ClampMax=50))
    int32 InitialTargetsQuantity;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Wave", meta = (ClampMin=1, ClampMax=15))
    int32 NeedKillToFinish;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Wave", meta = (ClampMin=1000, ClampMax=4000))
    int32 InitialSpawnRadius;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Wave", meta = (ClampMin=100, ClampMax=2000));
    int32 KillsCountingRadius;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Wave", meta = (ClampMin=10, ClampMax=250))
    int32 TargetsDistance;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Wave", meta = (ClampMin=20.f, ClampMax=100.f))
    float SpawnHeight;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Wave | Multipliers", meta = (ClampMin=1, ClampMax=100))
    int32 TargetsQuantityMulti;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Wave | Multipliers", meta = (ClampMin=1, ClampMax=100))
    int32 RadiusMulti;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Wave | Multipliers", meta = (ClampMin=0, ClampMax=100))
    int32 TargetSizeMultiStep;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Wave", meta = (ClampMin=0, ClampMax=10.f))
    float DelayBetweenWaves;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Wave", meta = (ClampMin=0.5f, ClampMax=2.f))
    float MinTargetSize;
    
public:
    ASGameMode();
    
    virtual void StartPlay() override;

    void StartWave();
    void SpawnTargets();
    void ResizeTarget(AActor* Target);
    void PrepareForWave();
    void FinishWave();

    void OnTargetKilledHandle(const AActor* Victim);
    
    FOnTargetKilled OnTargetKilled;
    FOnWaveFinished OnWaveFinished;
};
