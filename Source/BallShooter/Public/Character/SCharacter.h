// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class UCameraComponent;
class USWeaponComponent;

UCLASS()
class BALLSHOOTER_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
    UCameraComponent* CameraComp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
    USWeaponComponent* WeaponComp;

public:
	/** Sets default properties for SCharacter **/
	ASCharacter();

protected:
	/** Called when the game starts or when spawned **/
	virtual void BeginPlay() override;

    /** Forward/Backward moving **/
    void MoveForward(const float Amount);
    /** Right/Left moving **/
    void MoveRight(const float Amount);

public:	
	/** Bind functionality to input **/
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
