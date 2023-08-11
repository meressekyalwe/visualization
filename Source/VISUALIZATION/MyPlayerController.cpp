// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "VISUALIZATION.h"
#include "Kismet/GameplayStatics.h"

AMyPlayerController::AMyPlayerController()
{
    bShowMouseCursor = true;
    bEnableClickEvents = true;
    bEnableTouchEvents = true;

}

void AMyPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
}


