// Fill out your copyright notice in the Description page of Project Settings.


#include "SWeaponComponent.h"
#include "SWeapon.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
USWeaponComponent::USWeaponComponent()
{
    HandSocketName = "S_Hand_01";
}

void USWeaponComponent::Fire()
{
    if(!ensure(WeaponInstance)) return;
    WeaponInstance->Fire();
}


// Called when the game starts
void USWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
    if(!ensureMsgf(WeaponClass, TEXT("Weapon Component doesn't have any weapons class."))) return;

    SpawnWeapon();
}

void USWeaponComponent::SpawnWeapon()
{
    const auto Owner = GetOwner<ACharacter>();
    if(!GetWorld() || WeaponInstance || !Owner) return;
    
    FActorSpawnParameters SpawnParams;
    SpawnParams.Instigator = Owner;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    
    WeaponInstance = GetWorld()->SpawnActor<ASWeapon>(WeaponClass, SpawnParams);

    AttachWeaponToHand(Owner);
}

void USWeaponComponent::AttachWeaponToHand(const ACharacter* Owner) const
{
    if(!WeaponInstance) return;
    
    const FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, false);
    WeaponInstance->AttachToComponent(Owner->GetMesh(), AttachRules, HandSocketName);
}
