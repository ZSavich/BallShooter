// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "SWeaponComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
    GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    
    WeaponComp = CreateDefaultSubobject<USWeaponComponent>(TEXT("WeaponComponent"));
    
    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("FPPCamera"));
    CameraComp->SetupAttachment(GetCapsuleComponent());
    CameraComp->bUsePawnControlRotation = true;

    GetMesh()->SetupAttachment(CameraComp);
    GetMesh()->bCastDynamicShadow = false;
    GetMesh()->CastShadow = false;
    
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    
    if(!ensure(PlayerInputComponent)) return;
    
    // Jumping input
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

    // Firing input
    PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComp, &USWeaponComponent::Fire);

    // Movement inputs
    PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);

    // Turn & LookUp inputs 
    PlayerInputComponent->BindAxis("Turn", this, &ACharacter::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &ACharacter::AddControllerPitchInput);

}

void ASCharacter::MoveForward(const float Amount)
{
    if (Amount == 0.0f) return;
    
    // Add movement in forward/backward direction
    AddMovementInput(GetActorForwardVector(), Amount);
}

void ASCharacter::MoveRight(const float Amount)
{
    if (Amount == 0.0f) return;
    
    // Add movement in right/left direction
    AddMovementInput(GetActorRightVector(), Amount);
}