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
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon")
    USkeletalMeshComponent* WeaponMeshComp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon")
    TSubclassOf<ASProjectile> ProjectileClass;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Weapon")
    FName MuzzleSocketName;
    
public:	
	/** Sets default properties for Weapon **/
    ASWeapon();

protected:
	/** Called when the game starts or when spawned **/
	virtual void BeginPlay() override;

    FTransform GetSpawnTransform() const;

public:
    void Fire();
};
