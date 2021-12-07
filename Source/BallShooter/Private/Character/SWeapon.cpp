// Fill out your copyright notice in the Description page of Project Settings.


#include "SWeapon.h"

#include "CollisionDebugDrawingPublic.h"
#include "DrawDebugHelpers.h"
#include "SProjectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASWeapon::ASWeapon()
{
    WeaponMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
    WeaponMeshComp->bCastDynamicShadow = false;
    WeaponMeshComp->CastShadow = false;
    SetRootComponent(WeaponMeshComp);

    MuzzleSocketName = "S_Muzzle_01";
}

// Called when the game starts or when spawned
void ASWeapon::BeginPlay()
{
	Super::BeginPlay();

    if(!ensureMsgf(ProjectileClass, TEXT("Weapon doesn't have Projectile Class."))) return;
}

FTransform ASWeapon::GetSpawnTransform() const
{
    const auto OwnerPawn = GetInstigator();
    if(!OwnerPawn) return FTransform();
    
    const auto MuzzleLocation = WeaponMeshComp->GetSocketLocation(MuzzleSocketName);
    
    FVector ViewLocation;
    FRotator ViewRotation;
    OwnerPawn->GetController()->GetPlayerViewPoint(ViewLocation, ViewRotation);
    
    auto EndPointLocation = ViewLocation + (ViewRotation.Vector() * 2000.f);

    FHitResult HitResult;
    GetWorld()->LineTraceSingleByChannel(HitResult, ViewLocation, EndPointLocation, ECC_Visibility);

    EndPointLocation = HitResult.bBlockingHit ? HitResult.ImpactPoint : EndPointLocation;
    
    const auto SpawnRotation = FRotationMatrix::MakeFromX(EndPointLocation - MuzzleLocation).Rotator();
    
    return FTransform(SpawnRotation, MuzzleLocation);
}

void ASWeapon::Fire()
{
    if(!ProjectileClass) return;
    
    FActorSpawnParameters SpawnParams;
    SpawnParams.Instigator = GetInstigator();
    SpawnParams.Owner = this;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    GetWorld()->SpawnActor<ASProjectile>(ProjectileClass, GetSpawnTransform(), SpawnParams);
}
