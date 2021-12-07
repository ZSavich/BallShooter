// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SWeapon.generated.h"

class ASProjectile;

UCLASS()
class BALLSHOOTER_API ASWeapon : public AActor
{
	GENERATED_BODY()

protected:
    /** Pointer for the Weapon Mesh Component **/
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon")
    USkeletalMeshComponent* WeaponMeshComp;

    /** The Projectile Class for spawn **/
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon")
    TSubclassOf<ASProjectile> ProjectileClass;

    /** Muzzle socket in the Weapon Instance **/
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Weapon")
    FName MuzzleSocketName;

    /** Particle Effect for Shooting **/
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon")
    UParticleSystem* MuzzleEffect;
    
public:	
	/** Sets default properties for Weapon **/
    ASWeapon();

protected:
	/** Called when the game starts or when spawned **/
	virtual void BeginPlay() override;

    /** Calculates spawn's location and rotation for a Projectile **/
    FTransform GetSpawnTransform() const;

public:
    /** Spawning a Projectile from the Muzzle Socket **/
    void Fire();
};
