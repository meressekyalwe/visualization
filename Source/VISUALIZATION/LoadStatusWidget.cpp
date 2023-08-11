// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadStatusWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "VISUALIZATIONGameModeBase.h"
#include "Kismet/GameplayStatics.h"

bool ULoadStatusWidget::Initialize()
{
	Super::Initialize();

	PauseContinue->OnClicked.AddDynamic(this, &ULoadStatusWidget::PauseContinueClicked);

	Menu->OnClicked.AddDynamic(this, &ULoadStatusWidget::MenuClicked);

	RestartLoading->OnClicked.AddDynamic(this, &ULoadStatusWidget::RestartLoadingClicked);

	return true;
}


void ULoadStatusWidget::PauseContinueClicked()
{
	AVISUALIZATIONGameModeBase* GMB = GetWorld()->GetAuthGameMode<AVISUALIZATIONGameModeBase>();

	if (GMB)
	{
		if (GMB->bSpawnPaused == false)
		{
			GMB->bSpawnPaused = true;

			PauseContinueText->SetText(FText::FromString(("Continue")));
		}
		else if (GMB->bSpawnPaused == true)
		{
			GMB->bSpawnPaused = false;

			PauseContinueText->SetText(FText::FromString("Pause"));
		}
	}
}

void ULoadStatusWidget::MenuClicked()
{
	RemoveFromParent();
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void ULoadStatusWidget::RestartLoadingClicked()
{
	AVISUALIZATIONGameModeBase* GMB = GetWorld()->GetAuthGameMode<AVISUALIZATIONGameModeBase>();

	GMB->RestartLoading();

	RemoveFromParent();
}

void ULoadStatusWidget::SetLoadStatus(FString Text)
{
	LoadStatus->SetText(FText::FromString(Text));
}
