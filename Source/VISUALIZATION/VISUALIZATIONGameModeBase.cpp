// Fill out your copyright notice in the Description page of Project Settings.


#include "VISUALIZATIONGameModeBase.h"
#include "SpectatorCamera.h"
#include "MyPlayerController.h"
#include "Serialization/JsonSerializer.h"
#include "Engine.h" 
#include "LoadStatusWidget.h"
#include "Components/TextBlock.h"

TSharedPtr<FJsonObject> JsonObject;

AVISUALIZATIONGameModeBase::AVISUALIZATIONGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AVISUALIZATIONGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (MenuWidgetClass)
	{
		MW = Cast<UMenuWidget>(CreateWidget(GetWorld(), MenuWidgetClass));

		if (MW)
		{
			MW->AddToViewport();
		}
	}
}

void AVISUALIZATIONGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AVISUALIZATIONGameModeBase::ParseFile()
{
	GetData();

	if (FunctionalWidgetClass)
	{
		FW = Cast<UFunctionalWidget>(CreateWidget(GetWorld(), FunctionalWidgetClass));

		if (FW)
		{
			FW->AddToViewport();
		}
	}
}

bool AVISUALIZATIONGameModeBase::Deserialized()
{
	FString JsonString;

	FFileHelper::LoadFileToString(JsonString, *FileName);
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		ParseFile();

		return true;
	}

	return false;
}

void AVISUALIZATIONGameModeBase::GetData()
{
	TSharedPtr<FJsonObject> container = JsonObject->GetObjectField(TEXT("first_visual"))->GetObjectField(TEXT("loading_size"));

	Container.Size =  FVector(
		container->GetNumberField(TEXT("width")), 
		container->GetNumberField(TEXT("length")),
		container->GetNumberField(TEXT("height")));
	Container.Size += 0.005 * Container.Size;

	Container.Location = FVector(0.f, 0.f, 0.f);
	Container.Location.Z = - Container.Size.Z / 20;

	TSharedPtr<FJsonObject> containerData = JsonObject->GetObjectField(TEXT("first_visual"))->GetObjectField(TEXT("calculation_info"));

	Container.cargos_mass = containerData->GetNumberField("cargos_mass");
	Container.cargos_volume = containerData->GetNumberField("cargos_volume") / 1000000;
	Container.void_space_percent = containerData->GetNumberField("void_space_percent");
	Container.density_percent = containerData->GetNumberField("density_percent");



	TArray<TSharedPtr<FJsonValue>> DataBoxes = JsonObject->GetObjectField(TEXT("first_visual"))->GetArrayField(TEXT("boxes"));

	for (int i = 0; i < DataBoxes.Num(); ++i)
	{
		FBoxData Box;

		TSharedPtr<FJsonValue> Value = DataBoxes[i];
		TSharedPtr<FJsonObject> BoxData = Value->AsObject();

		Box.Title = BoxData->GetObjectField(TEXT("info"))->GetStringField(TEXT("title"));

		Box.Color = FColor::FromHex(BoxData->GetObjectField(TEXT("info"))->GetStringField(TEXT("color")));

		Box.Location = FVector(BoxData->GetObjectField(TEXT("position"))->GetNumberField(TEXT("z")),
			BoxData->GetObjectField(TEXT("position"))->GetNumberField(TEXT("x")),
			BoxData->GetObjectField(TEXT("position"))->GetNumberField(TEXT("y")) + 10 - Container.Size.Z / 2);

		Box.Size = FVector(BoxData->GetObjectField(TEXT("calculated_size"))->GetNumberField(TEXT("width")),
			BoxData->GetObjectField(TEXT("calculated_size"))->GetNumberField(TEXT("length")),
			BoxData->GetObjectField(TEXT("calculated_size"))->GetNumberField(TEXT("height")));

		Box.Weight = BoxData->GetNumberField("mass");

		Boxes.Add(Box);
	}

	DrawContainer();
}

void AVISUALIZATIONGameModeBase::DrawContainer()
{
	FTransform Transform(FRotator(0.0f, 0.0f, 0.f), Container.Location, Container.Size / 1000);
	AContainer* Cont = GetWorld()->SpawnActor<AContainer>(ContainerClass, Transform);
}

void AVISUALIZATIONGameModeBase::SpawnOneBox()
{
	if(Index < Boxes.Num() && bSpawnPaused == false)
	{
		FTransform Transform(FRotator(0.0f, 0.0f, 0.0f), Boxes[Index].Location / 10, Boxes[Index].Size / 1000);
		ASingleBox* SingleBox = GetWorld()->SpawnActor<ASingleBox>(SingleBoxClass, Transform);
		SingleBox->SetBoxData(Boxes[Index]);
		Index += 1;
	}

	LSW->SetLoadStatus(FString::FromInt(Index) + FString(" of ") + FString::FromInt(Boxes.Num()));

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AVISUALIZATIONGameModeBase::SpawnOneBox, 1.0f, false);
}

void AVISUALIZATIONGameModeBase::SpawnAllBoxes()
{
	if (LoadStatusWidgetClass)
	{
		LSW = Cast<ULoadStatusWidget>(CreateWidget(GetWorld(), LoadStatusWidgetClass));

		if (LSW)
		{
			LSW->AddToViewport();
		}
	}

	for (Index = 0; Index < Boxes.Num(); Index++)
	{
		FTransform Transform(FRotator(0.0f, 0.0f, 0.0f), Boxes[Index].Location / 10, Boxes[Index].Size / 1000);
		ASingleBox* SingleBox = GetWorld()->SpawnActor<ASingleBox>(SingleBoxClass, Transform);
		SingleBox->SetBoxData(Boxes[Index]);
	}

	LSW->SetLoadStatus(FString::FromInt(Index) + FString(" of ") + FString::FromInt(Boxes.Num()));

	if (Index >= 29) LSW->PauseContinueText->SetText(FText::FromString("load completed"));
}

void AVISUALIZATIONGameModeBase::SpawnBoxesOneByOne()
{
	Index = 0;
	bSpawnPaused = false;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AVISUALIZATIONGameModeBase::SpawnOneBox, 1.0f, false);

	if (LoadStatusWidgetClass)
	{
		LSW = Cast<ULoadStatusWidget>(CreateWidget(GetWorld(), LoadStatusWidgetClass));

		if (LSW)
		{
			LSW->AddToViewport();
		}
	}

	if (Index >= 29) LSW->PauseContinueText->SetText(FText::FromString("load completed"));
}

void AVISUALIZATIONGameModeBase::RestartLoading()
{
	TArray<AActor*> SpawnedBoxes;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASingleBox::StaticClass(), SpawnedBoxes);

	for (AActor* TActor : SpawnedBoxes)
	{
		ASingleBox* MySingleBox = Cast<ASingleBox>(TActor);

		if (MySingleBox != nullptr)
		{
			MySingleBox->Destroy();
		}
	}

	bSpawnPaused = true;
	Index = 0;

	if (FunctionalWidgetClass)
	{
		FW = Cast<UFunctionalWidget>(CreateWidget(GetWorld(), FunctionalWidgetClass));

		if (FW)
		{
			FW->AddToViewport();
		}
	}
}






