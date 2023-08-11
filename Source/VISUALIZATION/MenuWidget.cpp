// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"
#include "Components/Button.h"
#include "VISUALIZATIONGameModeBase.h"


bool UMenuWidget::Initialize()
{
	Super::Initialize();

	//OpenFile->OnClicked.AddDynamic(this, &UMenuWidget::OpenFileButtonClicked);

	return true;
}

void UMenuWidget::OpenFileButtonClicked(FString Path)
{
	AVISUALIZATIONGameModeBase* GMB = GetWorld()->GetAuthGameMode<AVISUALIZATIONGameModeBase>();

	if (GMB)
	{
		GMB->FileName = Path;

		if (GMB->Deserialized())
		{
			RemoveFromParent();
		}
	}
}
