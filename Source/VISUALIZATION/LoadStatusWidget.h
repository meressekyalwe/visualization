// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoadStatusWidget.generated.h"


UCLASS()
class VISUALIZATION_API ULoadStatusWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual bool Initialize();

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Title;

	UPROPERTY(meta = (BindWidget))
	class UButton* PauseContinue;

	UPROPERTY(meta = (BindWidget))
	class UButton* Menu;

	UPROPERTY(meta = (BindWidget))
	class UButton* RestartLoading;

	UFUNCTION()
	void PauseContinueClicked();

	UFUNCTION()
	void MenuClicked();

	UFUNCTION()
	void RestartLoadingClicked();

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* LoadStatus;

public:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PauseContinueText;

	void SetLoadStatus(FString Text);	
};
