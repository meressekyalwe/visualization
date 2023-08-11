// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FunctionalWidget.generated.h"


UCLASS()
class VISUALIZATION_API UFunctionalWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual bool Initialize();

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Title;

	UPROPERTY(meta = (BindWidget))
	class UButton* InOneGo;

	UPROPERTY(meta = (BindWidget))
	class UButton* OneByOne;

	UFUNCTION()
	void InOneGoClicked();

	UFUNCTION()
	void OneByOneClicked();
	
};
