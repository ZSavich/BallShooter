// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SProjectile.h"

#include "DrawDebugHelpers.h"
#include "Components/SphereComponent.h"

// Sets default values
ASProjectile::ASProjectile()
{
    // Create and set up default properties for the Sphere Collision
    SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
    SphereCollision->IgnoreActorWhenMoving(GetInstigator<AActor>(), true);
    SphereCollision->IgnoreActorWhenMoving(GetOwner(), true);
    SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    SphereCollision->SetCollisionResponseToAllChannels(ECR_Block);
    SphereCollision->SetSimulatePhysics(true);
    SetRootComponent(SphereCollision);

    // Create and set up default properties for the Projectile's Mesh
    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    MeshComp->SetupAttachment(SphereCollision);

    // Create the Projectile Movement Component 
    MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));

    // Default custom properties
    LifeSpan = 5.f;
}

// Called when the game starts or when spawned
void ASProjectile::BeginPlay()
{
	Super::BeginPlay();

    // Destroy actor in life span time
    SetLifeSpan(LifeSpan);
}

// Called between Constructor and BeginPlay
void ASProjectile::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    SphereCollision->OnComponentHit.AddDynamic(this, &ASProjectile::OnProjectileHit);
}

// Called when projectile hit object with hit reaction 
void ASProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    FVector NormalImpulse, const FHitResult& Hit)
{
    DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 16.f, 32.f, FColor::Green, false, 5.f, 0.f, 1.f);
    Destroy();
}
