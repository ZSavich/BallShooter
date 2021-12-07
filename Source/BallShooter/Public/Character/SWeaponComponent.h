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
    /** Default Weapon Class **/
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="WeaponComponent")
    TSubclassOf<ASWeapon> WeaponClass;

    /** Pointer to the Weapon instance that was created from Weapon Class **/
    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="WeaponComponent")
    ASWeapon* WeaponInstance;

    /** Socket in the Character Mesh for the Weapon attaching **/
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="WeaponComponent")
    FName HandSocketName;
    
public:	
    /** Sets default properties for SWeaponComponent **/
	USWeaponComponent();

    /** Called when player presses the "Fire" input **/
    UFUNCTION(BlueprintCallable)
    void Fire();

protected:
	/** Called when the game starts **/
	virtual void BeginPlay() override;

    /** Spawns the Weapon at the BeginPlay **/
    void SpawnWeapon();
    
    /** Attaches the Weapon to the Character Mesh's Hand socket **/
    void AttachWeaponToHand(const ACharacter* Owner) const;

};
