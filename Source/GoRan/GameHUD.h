// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameHUD.generated.h"

class UDistanceWidget;

/**
 * 
 */
UCLASS()
class GORAN_API AGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category="GameHUD")
	UDistanceWidget* GetDistanceWidget() const;

private:
	UPROPERTY(EditAnywhere, Category = "GameHUD")
	TSubclassOf<UDistanceWidget> DistanceWidgetClass;

	UPROPERTY(meta = (BindWidget))
	UDistanceWidget* _distanceWidget;
};
