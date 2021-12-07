// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SWeaponComponent.generated.h"

class ASWeapon;
class ASCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BALLSHOOTER_API USWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="WeaponComponent")
    TSubclassOf<ASWeapon> WeaponClass;

    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="WeaponComponent")
    ASWeapon* WeaponInstance;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="WeaponComponent")
    FName HandSocketName;
    
public:	
    /** Sets default properties for SWeaponComponent **/
	USWeaponComponent();

    UFUNCTION(BlueprintCallable)
    void Fire();

protected:
	/** Called when the game starts **/
	virtual void BeginPlay() override;

    void SpawnWeapon();
    void AttachWeaponToHand(const ACharacter* Owner) const;

};
