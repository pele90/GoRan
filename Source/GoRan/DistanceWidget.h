// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DistanceWidget.generated.h"

class UTextBlock;

UCLASS()
class GORAN_API UDistanceWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateDistance(float distance);

private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* _distanceText;
};
