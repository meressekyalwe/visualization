// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"


UCLASS()
class VISUALIZATION_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual bool Initialize();

	UPROPERTY(meta = (BindWidget))
	class UButton* OpenFile;

	UFUNCTION(BlueprintCallable, Category = "Event")
	void OpenFileButtonClicked(FString Path);

};
