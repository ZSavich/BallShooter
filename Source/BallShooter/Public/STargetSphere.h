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
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="TargetSphere")
    UStaticMeshComponent* MeshComp;
    
public:	
	/** Sets default values for this actor's properties **/
	ASTargetSphere();

protected:
	/** Called when the game starts or when spawned **/
	virtual void BeginPlay() override;
    virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

};
