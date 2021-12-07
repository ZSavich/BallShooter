// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "SProjectile.generated.h"

class USphereComponent;

UCLASS()
class BALLSHOOTER_API ASProjectile : public AActor
{
	GENERATED_BODY()

    FVector ShotDirection;
    
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Projectile")
    UStaticMeshComponent* MeshComp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Collision")
    USphereComponent* SphereCollision;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    UProjectileMovementComponent* MovementComp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Projectile")
    float LifeSpan;
	
public:	
	/** Sets default properties for SProjectile **/
	ASProjectile();

protected:
	/** Called when the game starts or when spawned **/
	virtual void BeginPlay() override;
    virtual void PostInitializeComponents() override;

    UFUNCTION()
    void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
