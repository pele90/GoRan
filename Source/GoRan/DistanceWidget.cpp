// Fill out your copyright notice in the Description page of Project Settings.


#include "DistanceWidget.h"
#include "Components/TextBlock.h"

#define LOCTEXT_NAMESPACE "GUI Distance"

void UDistanceWidget::UpdateDistance(float distance)
{
	if (_distanceText == nullptr)
	{
		return;
	}

	float distanceInMeters = distance / 100.0f;

	FText distanceText = FText::Format(LOCTEXT("Distance", "Distance covered: {0} meters"), (int)distanceInMeters);
	_distanceText->SetText(distanceText);
}

#undef LOCTEXT_NAMESPACE