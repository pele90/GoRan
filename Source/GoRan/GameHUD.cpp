// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"
#include "DistanceWidget.h"

void AGameHUD::DrawHUD()
{
	Super::DrawHUD();
}

void AGameHUD::BeginPlay()
{
	Super::BeginPlay();

	if (DistanceWidgetClass != nullptr)
	{
		_distanceWidget = CreateWidget<UDistanceWidget>(GetWorld(), DistanceWidgetClass);

		if (_distanceWidget)
		{
			_distanceWidget->AddToViewport();
		}
	}
}

UDistanceWidget* AGameHUD::GetDistanceWidget() const
{
	return _distanceWidget;
}
