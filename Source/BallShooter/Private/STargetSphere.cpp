// Fill out your copyright notice in the Description page of Project Settings.


#include "STargetSphere.h"

#include "SGameMode.h"
#include "SProjectile.h"

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

void ASTargetSphere::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved,
    FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
    Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

    // Handle only Projectile Actors
    if(!Other->IsA<ASProjectile>()) return;

    // Find Game Mode Class of the Level
    const auto GM = GetWorld()->GetAuthGameMode<ASGameMode>();
    if(!ensure(GM)) return;

    // Calls the assigns of OnTargetKilled delegate
    GM->OnTargetKilled.Broadcast(this);
    // Immediately to destroy this actor
    Destroy();
}
