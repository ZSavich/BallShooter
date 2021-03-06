// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SProjectile.h"

#include "DrawDebugHelpers.h"
#include "Components/SphereComponent.h"

// Sets default values
ASProjectile::ASProjectile()
{
    // Create and set up default properties for the Sphere Collision
    SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
    SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    SphereCollision->SetCollisionResponseToAllChannels(ECR_Block);
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

    
    SphereCollision->IgnoreActorWhenMoving(GetInstigator(), true);
    SphereCollision->IgnoreActorWhenMoving(GetOwner(), true);
    
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
    Destroy();
}
