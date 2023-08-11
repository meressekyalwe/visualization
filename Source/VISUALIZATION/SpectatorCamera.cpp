// Fill out your copyright notice in the Description page of Project Settings.


#include "SpectatorCamera.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

ASpectatorCamera::ASpectatorCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 750.0f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->bDoCollisionTest = false;


	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void ASpectatorCamera::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ASpectatorCamera::BeginPlay()
{
	Super::BeginPlay();
}


void ASpectatorCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAction("ZoomIn", IE_Pressed, this, &ASpectatorCamera::CameraZoomIn);
	PlayerInputComponent->BindAction("ZoomOut", IE_Pressed, this, &ASpectatorCamera::CameraZoomOut);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);//
	PlayerInputComponent->BindAxis("TurnRate", this, &ASpectatorCamera::TurnAtRate);//
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);//
	PlayerInputComponent->BindAxis("LookUpRate", this, &ASpectatorCamera::LookUpAtRate);//
}

void ASpectatorCamera::CameraZoomIn()
{
	if (CameraBoom->TargetArmLength <= 75.0)
	{
		CameraBoom->TargetArmLength = 75.0;
	}
	else
	{
		CameraBoom->TargetArmLength -=  (0.1 * CameraBoom->TargetArmLength);
	}
}

void ASpectatorCamera::CameraZoomOut()
{
	if (CameraBoom->TargetArmLength >= 3000)
	{
		CameraBoom->TargetArmLength = 3000;
	}
	else
	{
		CameraBoom->TargetArmLength += (0.1 * CameraBoom->TargetArmLength);
	}
}

void ASpectatorCamera::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ASpectatorCamera::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}


