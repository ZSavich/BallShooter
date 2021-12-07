// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameMode.h"

#include "DrawDebugHelpers.h"
#include "NavigationSystem.h"
#include "STargetSphere.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

ASGameMode::ASGameMode()
{
    InitialTargetsQuantity = 15;
    NeedKillToFinish = 10;
    InitialSpawnRadius = 2000;
    KillsCountingRadius = 1500;
    TargetsDistance = 80;
    SpawnHeight = 100.f;
    TargetsQuantityMulti = 10;
    RadiusMulti = 5;
    WavesCount = 1;
    DelayBetweenWaves = 5.f;
    MinTargetSize = 1.f;
    MaxTargetSize = 1.f;
    TargetSizeMultiStep = 1;
    
    OnTargetKilled.AddUObject(this, &ASGameMode::OnTargetKilledHandle);
}

void ASGameMode::StartPlay()
{
    Super::StartPlay();
    StartWave();
}

void ASGameMode::StartWave()
{
    const auto Player = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
    if(!ensure(Player)) return;

    PlayerLocation = Player->GetActorLocation();
    KillsCount = NeedKillToFinish;

    DrawDebugSphere(GetWorld(), PlayerLocation, KillsCountingRadius, 32.f, FColor::Red, true);
    SpawnTargets();
}

void ASGameMode::SpawnTargets()
{
    int32 TargetsCounter = 0;
    
    FNavLocation NavLocation;
    TArray<AActor*> OverlapResults;
    
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
    
    const auto NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
    
    for(int32 i = 0; i < InitialTargetsQuantity; ++i)
    {
        const auto SpawnRadius = TargetsCounter > NeedKillToFinish ? InitialSpawnRadius : KillsCountingRadius; 
        NavSystem->GetRandomPointInNavigableRadius(PlayerLocation, SpawnRadius, NavLocation);

        const auto SpawnLocation = NavLocation.Location + FVector(0.f,0.f, SpawnHeight);

        const bool bIsOverlapOther = UKismetSystemLibrary::SphereOverlapActors(GetWorld(), SpawnLocation, TargetsDistance,{},TargetSphereClass,{},OverlapResults);
        if(bIsOverlapOther)
        {
            --i;
            continue;
        }

        const auto SpawnedTarget = GetWorld()->SpawnActor<ASTargetSphere>(TargetSphereClass, SpawnLocation , FRotator::ZeroRotator, SpawnParams);
        if(!SpawnedTarget)
        {
            --i;
            continue;
        }

        ResizeTarget(SpawnedTarget);
        TargetInstances.Add(SpawnedTarget);
        TargetsCounter++;
    }
}

void ASGameMode::ResizeTarget(AActor* Target)
{
    if(TargetSizeMultiStep <= 0) return;

    const auto TargetSize = Target->GetActorScale3D();
    const auto NewTargetSize = TargetSize * MinTargetSize * TargetSizeMultiStep;
    Target->SetActorScale3D(NewTargetSize);
}

void ASGameMode::PrepareForWave()
{
    InitialTargetsQuantity = InitialTargetsQuantity * TargetsQuantityMulti / 100 + InitialTargetsQuantity;
    InitialSpawnRadius = InitialSpawnRadius * RadiusMulti / 100 + InitialSpawnRadius;
    ++WavesCount;

    FTimerHandle TimerHandle_StartNewWave;
    GetWorldTimerManager().SetTimer(TimerHandle_StartNewWave, this, &ASGameMode::StartWave, DelayBetweenWaves, false);
}

void ASGameMode::FinishWave()
{
    if(TargetInstances.Num())
    {
        for(const auto Instance : TargetInstances)
        {
            Instance->Destroy();
        }
    }
    
    TargetInstances.Empty();
    OnWaveFinished.Broadcast();
    PrepareForWave();
}

void ASGameMode::OnTargetKilledHandle(const AActor* Victim)
{
    if(!Victim) return;
    
    const auto Radius = (Victim->GetActorLocation() - PlayerLocation).Size();
    if(Radius <= KillsCountingRadius) KillsCount--;
    if(KillsCount <= 0) FinishWave();
}
