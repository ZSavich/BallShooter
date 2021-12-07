// Fill out your copyright notice in the Description page of Project Settings.


#include "SWeaponComponent.h"
#include "SWeapon.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
USWeaponComponent::USWeaponComponent()
{
    // Set default name for hand socket in character mesh
    HandSocketName = "S_Hand_01";
}

// Called when player press input "Fire"
void USWeaponComponent::Fire()
{
    if(!ensure(WeaponInstance)) return;
    WeaponInstance->Fire();
}


// Calls when the game starts
void USWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
    if(!ensureMsgf(WeaponClass, TEXT("Weapon Component doesn't have any weapons class."))) return;

    // Spawns the Weapon Instance when game stars
    SpawnWeapon();
}

// Spawns the weapon instance for character class
void USWeaponComponent::SpawnWeapon()
{
    const auto Owner = GetOwner<ACharacter>();
    if(!GetWorld() || WeaponInstance || !Owner) return;
    
    FActorSpawnParameters SpawnParams;
    SpawnParams.Instigator = Owner;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    
    WeaponInstance = GetWorld()->SpawnActor<ASWeapon>(WeaponClass, SpawnParams);

    // Attack the weapon to the hand socket
    AttachWeaponToHand(Owner);
}

// Calls in order to attach the weapon to hand socket in the character mesh
void USWeaponComponent::AttachWeaponToHand(const ACharacter* Owner) const
{
    if(!WeaponInstance) return;
    
    const FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, false);
    WeaponInstance->AttachToComponent(Owner->GetMesh(), AttachRules, HandSocketName);
}
