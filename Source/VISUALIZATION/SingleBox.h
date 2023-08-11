// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Types.h"
#include "SingleBox.generated.h"

UCLASS()
class VISUALIZATION_API ASingleBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASingleBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSelected(AActor* Target, FKey ButtonPressed);

public:

	UFUNCTION()
	void SetBoxData(FBoxData InData);

private:

	UPROPERTY()
	class UStaticMeshComponent* Mesh;

	UPROPERTY()
	FBoxData Data;
};
