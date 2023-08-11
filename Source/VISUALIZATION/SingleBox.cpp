// Fill out your copyright notice in the Description page of Project Settings.


#include "SingleBox.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "VISUALIZATIONGameModeBase.h"
#include "Engine/World.h"
#include "Engine/StaticMesh.h"
#include "Components/PrimitiveComponent.h"


// Sets default values
ASingleBox::ASingleBox()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));

	Mesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/Geometies/Meshes/1M_Cube_Chamfer.1M_Cube_Chamfer'"));

	if (MeshAsset.Succeeded())
	{
		Mesh->SetStaticMesh(MeshAsset.Object);
	}	
}


void ASingleBox::BeginPlay()
{
	Super::BeginPlay();

	OnClicked.AddDynamic(this, &ASingleBox::OnSelected);
}

void ASingleBox::OnSelected(AActor* Target, FKey ButtonPressed)
{
	AVISUALIZATIONGameModeBase* GMB = GetWorld()->GetAuthGameMode<AVISUALIZATIONGameModeBase>();

	if (GMB)
	{
		GMB->ClickedBox = Data;
	}
}

void ASingleBox::SetBoxData(FBoxData InData)
{
	Data = InData;

	UMaterialInstanceDynamic* Material = Mesh->CreateAndSetMaterialInstanceDynamic(0);

	if (Material != nullptr)
	{
		Material->SetVectorParameterValue(FName("Color"), Data.Color);
	}
}





