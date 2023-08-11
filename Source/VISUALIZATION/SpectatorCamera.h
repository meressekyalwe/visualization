// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "SpectatorCamera.generated.h"


UCLASS()
class VISUALIZATION_API ASpectatorCamera : public ASpectatorPawn
{
	GENERATED_BODY()

public:

	ASpectatorCamera();

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* FollowCamera;

protected:

	void CameraZoomIn();

	void CameraZoomOut();

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;


public:


	FORCEINLINE  USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	FORCEINLINE  UCameraComponent* GetFollowCamera() const { return FollowCamera; }

};
