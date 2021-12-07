// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SProjectile.h"

#include "DrawDebugHelpers.h"
#include "Components/SphereComponent.h"

// Sets default values
ASProjectile::ASProjectile()
{
    SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
    SphereCollision->IgnoreActorWhenMoving(GetInstigator<AActor>(), true);
    SphereCollision->IgnoreActorWhenMoving(GetOwner(), true);
    SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    SphereCollision->SetCollisionResponseToAllChannels(ECR_Block);
    SphereCollision->SetSimulatePhysics(true);
    SetRootComponent(SphereCollision);
    
    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    MeshComp->SetupAttachment(SphereCollision);

    MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
    
    LifeSpan = 5.f;
}

// Called when the game starts or when spawned
void ASProjectile::BeginPlay()
{
	Super::BeginPlay();

    MovementComp->Velocity = ShotDirection * MovementComp->InitialSpeed;
    
    SetLifeSpan(5.f);
}

void ASProjectile::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    SphereCollision->OnComponentHit.AddDynamic(this, &ASProjectile::OnProjectileHit);
}

void ASProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    FVector NormalImpulse, const FHitResult& Hit)
{
    DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 16.f, 32.f, FColor::Green, false, 5.f, 0.f, 1.f);
    Destroy();
}
