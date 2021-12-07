// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameMode.h"

#include "DrawDebugHelpers.h"
#include "NavigationSystem.h"
#include "SPlayerState.h"
#include "STargetSphere.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

ASGameMode::ASGameMode()
{
    // The Target's properties
    InitialTargetsQuantity = 15;
    MinTargetSize = 1.f;
    NeedKillToFinish = 10;
    TargetsDistance = 80;
    SpawnHeight = 100.f;
    
    // The wave's properties
    InitialSpawnRadius = 2000;
    KillsCountingRadius = 1500;
    DelayBetweenWaves = 2.f;
    WavesCount = 1;
    
    // The multiplier properties
    TargetsQuantityMulti = 10;
    RadiusMulti = 5;
    TargetSizeMultiStep = 0.1f;

    // Bind the OnTargetKilled delegate to the handle 
    OnTargetKilled.AddUObject(this, &ASGameMode::OnTargetKilledHandle);
}

void ASGameMode::StartPlay()
{
    Super::StartPlay();

    MaxTargetSize = MinTargetSize;

    // Start a wave when the game is ready
    StartWave();
}

// Finds Player's location where need to mark up the center of spawn system 
void ASGameMode::StartWave()
{
    const auto Player = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
    if(!ensure(Player)) return;

    PlayerLocation = Player->GetActorLocation();
    DestroyedRightTargets = NeedKillToFinish;
    
    SpawnTargets();
}

// Random spawning the Target Actors
void ASGameMode::SpawnTargets()
{
    // How many Target Actors have been spawned
    int32 TargetsCounter = 0;
    
    FNavLocation NavLocation;
    TArray<AActor*> OverlapResults;

    // Adjust Target Actor's location in order to correct spawn
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

    // Finds Navigation Volume where system can spawns the Targets
    const auto NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

    // Cycle of spawning the Targets with proper properties
    for(int32 i = 0; i < InitialTargetsQuantity; ++i)
    {
        // Finds the Radius for the Target Actor
        const auto SpawnRadius = TargetsCounter > NeedKillToFinish ? InitialSpawnRadius : KillsCountingRadius; 
        // Finds a Random Point within the specified radius
        NavSystem->GetRandomPointInNavigableRadius(PlayerLocation, SpawnRadius, NavLocation);
        // Setups the Target Actor's spawn point height
        const auto SpawnLocation = NavLocation.Location + FVector(0.f,0.f, SpawnHeight);

        // If we find another Target within the specified radius, we will stop the spawning
        const bool bIsOverlapOther = UKismetSystemLibrary::SphereOverlapActors(GetWorld(), SpawnLocation, TargetsDistance,{},TargetSphereClass,{},OverlapResults);
        if(bIsOverlapOther)
        {
            --i;
            continue;
        }

        // If we spawned the Target within another object, we will stop the spawning
        const auto SpawnedTarget = GetWorld()->SpawnActor<ASTargetSphere>(TargetSphereClass, SpawnLocation , FRotator::ZeroRotator, SpawnParams);
        if(!SpawnedTarget)
        {
            --i;
            continue;
        }

        // If everything is fine, we will change the Target's Size and added it to the Target's Array
        ResizeTarget(SpawnedTarget);
        TargetInstances.Add(SpawnedTarget);
        TargetsCounter++;
    }
}

// Changes every Target's size with specified step
void ASGameMode::ResizeTarget(AActor* Target)
{
    // If the change step is not specified, we will close this function
    if(TargetSizeMultiStep <= 0) return;

    // Get default size of the Target
    const auto TargetSize = Target->GetActorScale3D();
    // Change the Target's size 
    const auto NewTargetSize = TargetSize * MaxTargetSize;
    // Saves the Target's Size for next the Targets 
    MaxTargetSize += TargetSizeMultiStep;
    // Set a new size to the Target
    Target->SetActorScale3D(NewTargetSize);
}

// Multiplies Targets quantity, Spawn radius and starts a timer for a new wave
void ASGameMode::PrepareForWave()
{
    // Multiply properties in order to complicate the game
    InitialTargetsQuantity = InitialTargetsQuantity * TargetsQuantityMulti / 100 + InitialTargetsQuantity;
    InitialSpawnRadius = InitialSpawnRadius * RadiusMulti / 100 + InitialSpawnRadius;
    // Refresh the Max Target's size
    MaxTargetSize = MinTargetSize;

    // Starts the timer for new wave
    FTimerHandle TimerHandle_StartNewWave;
    GetWorldTimerManager().SetTimer(TimerHandle_StartNewWave, this, &ASGameMode::StartWave, DelayBetweenWaves, false);
}

// Completes the active wave and destroys all Targets
void ASGameMode::FinishWave()
{
    // If there's another targets, we will destroy them
    if(TargetInstances.Num())
    {
        for(const auto Instance : TargetInstances)
        {
            if(IsValid(Instance)) Instance->Destroy();
        }
    }

    // Clean the Target's Array
    TargetInstances.Empty();
    // Increase score of the waves
    ++WavesCount;
    // Called wave finished delegate
    OnWaveFinished.Broadcast();
    // Preparing the game mode for new wave
    PrepareForWave();
}

// The delegate that calls every kill of Targets
void ASGameMode::OnTargetKilledHandle(const AActor* Victim)
{
    if(!Victim) return;
    
    // Figure out if it's an important Target    
    const auto Radius = (Victim->GetActorLocation() - PlayerLocation).Size();
    // If this is, we will decrease the right targets counter in order to finish a wave
    if(Radius <= KillsCountingRadius) DestroyedRightTargets--;
    // If the right targets counter empty, we will finish a wave
    if(DestroyedRightTargets <= 0) FinishWave();
}
