// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "CoreMinimal.h"
#include "Types.generated.h"

USTRUCT(BlueprintType)
struct FBoxData
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Event")
	FString Title;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Event")
	float Weight;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Event")
	FVector Size;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Event")
	FColor Color;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Event")
	FVector Location;	
};

USTRUCT(BlueprintType)
struct FContainerData
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Event")
	FVector Size;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Event")
	FVector Location;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Event")
	float cargos_mass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Event")
	float cargos_volume;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Event")
	float void_space_percent;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Event")
	float density_percent;
};

UCLASS()
class VISUALIZATION_API UTypes : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
};
