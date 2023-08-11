// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Types.h"
#include "SingleBox.h"
#include "MenuWidget.h"
#include "FunctionalWidget.h"
#include "LoadStatusWidget.h"
#include "TimerManager.h"
#include "Container.h"
#include "VISUALIZATIONGameModeBase.generated.h"


UCLASS()
class VISUALIZATION_API AVISUALIZATIONGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	AVISUALIZATIONGameModeBase();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void ParseFile();

	UFUNCTION(BlueprintCallable, Category = "Event")
	bool Deserialized();

	void GetData();

	void DrawContainer();

	UFUNCTION()
	void SpawnOneBox();

	void SpawnAllBoxes();

	void SpawnBoxesOneByOne();

	void RestartLoading();

	bool bSpawnPaused = false;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Event")
	FBoxData ClickedBox;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Event")
	FContainerData Container;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Event")
	FString FileName;

	int Index = 0;

private:

	TArray<FBoxData> Boxes;

	FTimerHandle TimerHandle;

	FTimerDelegate Delegate;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASingleBox> SingleBoxClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AContainer> ContainerClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMenuWidget> MenuWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UFunctionalWidget> FunctionalWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ULoadStatusWidget> LoadStatusWidgetClass;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	class UMenuWidget* MW;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	class UFunctionalWidget* FW;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	class ULoadStatusWidget* LSW;
};

