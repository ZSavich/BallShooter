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

    //~=============================================================================
    //  Private properties that are using only in the Game Mode
    
    /** Array of the spawned Target Instances **/
    TArray<AActor*> TargetInstances;
    /** Gets the Player's Location when a wave starts **/
    FVector PlayerLocation;
    /** Count of Destroyed Targets that allows to finish a Wave **/
    int32 DestroyedRightTargets;
    /** Count of Waves **/
    int32 WavesCount;
    /** Max Size of Targets **/
    float MaxTargetSize;

    
protected:
    //~=============================================================================
    //  General properties for Waves
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Wave", meta = (ClampMin=1, ClampMax=15))
    int32 NeedKillToFinish;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Wave", meta = (ClampMin=0, ClampMax=10.f))
    float DelayBetweenWaves;
    
    //~=============================================================================
    //  Properties about a Wave Radius

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Wave| Radius", meta = (ClampMin=1000, ClampMax=4000))
    int32 InitialSpawnRadius;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Wave| Radius", meta = (ClampMin=100, ClampMax=2000));
    int32 KillsCountingRadius;

    //~=============================================================================
    //  Properties for the Targets
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Wave | Targets")
    TSubclassOf<ASTargetSphere> TargetSphereClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Wave | Targets", meta = (ClampMin=10, ClampMax=25))
    int32 InitialTargetsQuantity;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Wave | Targets", meta = (ClampMin=10, ClampMax=250))
    int32 TargetsDistance;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Wave| Targets", meta = (ClampMin=20.f, ClampMax=100.f))
    float SpawnHeight;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Wave| Targets", meta = (ClampMin=0.4f, ClampMax=10.f))
    float MinTargetSize;

    //~=============================================================================
    //  Properties that changes Radius and the Targets every wave 

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Wave | Multipliers", meta = (ClampMin=1, ClampMax=50))
    int32 TargetsQuantityMulti;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Wave | Multipliers", meta = (ClampMin=1, ClampMax=50))
    int32 RadiusMulti;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Wave | Multipliers", meta = (ClampMin=0.1, ClampMax=1))
    float TargetSizeMultiStep;
    
public:
    /** Constructor with default properties **/
    ASGameMode();

    /** Called when the Level Created **/
    virtual void StartPlay() override;

    /** Records important properties and starts creating the Targets **/
    void StartWave();
    /** Cycle that spawns the Targets depending on the Game Mode's properties **/
    void SpawnTargets();
    /** Changes Size of Target Actor **/
    void ResizeTarget(AActor* Target);
    /** Multiplies Params in order to complicate the game **/
    void PrepareForWave();
    /** Destroy all Targets for a new wave**/
    void FinishWave();

    /** Handle for delegate for UI **/
    void OnTargetKilledHandle(const AActor* Victim);

    /** Delegates **/
    FOnTargetKilled OnTargetKilled;
    FOnWaveFinished OnWaveFinished;
};
