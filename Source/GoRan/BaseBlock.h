// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseBlock.generated.h"

UCLASS()
class GORAN_API ABaseBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseBlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FName _connectingSocket;

	FVector _velocity;

	UPROPERTY(EditAnywhere, Category = "Difficulty")
	float _difficultyModifierIncreaseAmount = 2.0f;

	UPROPERTY(EditAnywhere, Category = "Difficulty")
	float _timeToStartIncreaseDifficultyModifier;

	UPROPERTY(EditAnywhere, Category = "Difficulty")
	float _horizontalSpeed = 1.0f;

	bool _bIncreasDifficultyModifier;

	float _gameTimer;

};
