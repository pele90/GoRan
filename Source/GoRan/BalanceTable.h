// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BalanceTable.generated.h"

/**
 * 
 */
UCLASS()
class GORAN_API UBalanceTable : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Difficulty")
	TArray<float> MinPlatformValues;

	UPROPERTY(EditAnywhere, Category = "Difficulty")
	TArray<float> MaxPlatformValues;

	UPROPERTY(EditAnywhere, Category = "Difficulty")
	TArray<float> MinDistanceValues;

	UPROPERTY(EditAnywhere, Category = "Difficulty")
	TArray<float> MaxDistanceValues;

	UPROPERTY(EditAnywhere, Category = "Difficulty")
	TArray<float> MinHeightValues;

	UPROPERTY(EditAnywhere, Category = "Difficulty")
	TArray<float> MaxHeightValues;
};
