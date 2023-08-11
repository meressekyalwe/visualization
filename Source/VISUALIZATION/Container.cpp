// Fill out your copyright notice in the Description page of Project Settings.


#include "Container.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "VISUALIZATIONGameModeBase.h"
#include "Engine/World.h"
#include "Engine/StaticMesh.h"
#include "Components/PrimitiveComponent.h"


// Sets default values
AContainer::AContainer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));

	Mesh->SetupAttachment(RootComponent);

	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/Geometies/Meshes/Shape_Cube.Shape_Cube'"));

	if (MeshAsset.Succeeded())
	{
		Mesh->SetStaticMesh(MeshAsset.Object);
	}
}

// Called when the game starts or when spawned
void AContainer::BeginPlay()
{
	Super::BeginPlay();	
}


