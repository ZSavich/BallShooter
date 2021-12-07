// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STargetSphere.generated.h"

UCLASS()
class BALLSHOOTER_API ASTargetSphere : public AActor
{
	GENERATED_BODY()

protected:
    /** Spawn Static Mesh Component for the Target Sphere **/
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="TargetSphere")
    UStaticMeshComponent* MeshComp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Effects")
    UParticleSystem* ExplosionEffect;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Effects")
    USoundBase* ExplosionSound;
    
public:	
	/** Sets default values for this actor's properties **/
	ASTargetSphere();

protected:
	/** Called when the game starts or when spawned **/
	virtual void BeginPlay() override;
    /** Called when the Target destroying **/
    virtual void Destroyed() override;

    /** Called when the Target Sphere hit something **/
    virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

};
