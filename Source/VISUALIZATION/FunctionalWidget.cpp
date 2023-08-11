// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionalWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "VISUALIZATIONGameModeBase.h"


bool UFunctionalWidget::Initialize()
{
	Super::Initialize();

	InOneGo->OnClicked.AddDynamic(this, &UFunctionalWidget::InOneGoClicked);

	OneByOne->OnClicked.AddDynamic(this, &UFunctionalWidget::OneByOneClicked);

	return true;
}

void UFunctionalWidget::InOneGoClicked()
{
	AVISUALIZATIONGameModeBase* GMB = GetWorld()->GetAuthGameMode<AVISUALIZATIONGameModeBase>();

	if (GMB)
	{
		GMB->SpawnAllBoxes();

		RemoveFromParent();
	}
}

void UFunctionalWidget::OneByOneClicked()
{
	AVISUALIZATIONGameModeBase* GMB = GetWorld()->GetAuthGameMode<AVISUALIZATIONGameModeBase>();

	if (GMB)
	{
		GMB->SpawnBoxesOneByOne();

		RemoveFromParent();
	}
}
