// Fill out your copyright notice in the Description page of Project Settings.


#include "STargetSphere.h"

#include "SGameMode.h"
#include "SPlayerState.h"
#include "SProjectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASTargetSphere::ASTargetSphere()
{
    // Create and Setup Target Sphere Mesh
    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    MeshComp->SetCollisionResponseToAllChannels(ECR_Ignore);
    MeshComp->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);
    SetRootComponent(MeshComp);
}

// Called when the game starts or when spawned
void ASTargetSphere::BeginPlay()
{
	Super::BeginPlay();
}

void ASTargetSphere::Destroyed()
{
    if(ExplosionEffect)
    {
        const auto EmitterTransform = FTransform(FRotator::ZeroRotator, GetActorLocation(), GetActorScale() * 2);
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, EmitterTransform);
    }

    if(ExplosionSound)
    {
        UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ExplosionSound, GetActorLocation());
    }
    
    Super::Destroyed();
}

void ASTargetSphere::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved,
    FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
    Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

    // Handle only Projectile Actors
    if(!Other->IsA<ASProjectile>()) return;

    // Find the Projectile's owner
    const auto Player = Cast<APawn>(Other->GetInstigator());
    if(Player)
    {
        // Find the Player's State
        const auto PlayerState = Player->GetPlayerState<ASPlayerState>();
        if(!ensure(PlayerState)) return;
        // Increase the the player score
        PlayerState->IncreaseKillsScore();
    }
    
    // Find Game Mode Class of the Level
    const auto GM = GetWorld()->GetAuthGameMode<ASGameMode>();
    if(!ensure(GM)) return;
    
    
    // Calls the assigns of OnTargetKilled delegate
    GM->OnTargetKilled.Broadcast(this);
    // Immediately to destroy this actor
    Destroy();
}
