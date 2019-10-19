// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/Queue.h"
#include "LevelGenerator.generated.h"

class APlayerCharacter;
class UBalanceTable;

UCLASS()
class GORAN_API ALevelGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CreateStartPlatform();

	FVector GetNewLocation(AActor* lastPlatform, AActor* newPlatform);

	void UpdateDifficultyParameters();

private:
	UPROPERTY(EditAnywhere, Category = "LevelGenerator")
	TSubclassOf<AActor> _platformClass;

	UPROPERTY(EditAnywhere, Category = "LevelGenerator")
	UBalanceTable* _balanceTable;

	UPROPERTY(EditAnywhere, Category = "LevelGenerator")
	float _minPlatformSize;
	
	UPROPERTY(EditAnywhere, Category = "LevelGenerator")
	float _maxPlatformSize;

	UPROPERTY(EditAnywhere, Category = "LevelGenerator")
	float _minHorizontalDistance;

	UPROPERTY(EditAnywhere, Category = "LevelGenerator")
	float _maxHorizontalDistance;

	UPROPERTY(EditAnywhere, Category = "LevelGenerator")
	float _minVerticalDistance;

	UPROPERTY(EditAnywhere, Category = "LevelGenerator")
	float _maxVerticalDistance;

	UPROPERTY(EditAnywhere, Category = "LevelGenerator")
	float _distanceToSpawnPlatform;

	UPROPERTY(EditAnywhere, Category = "LevelGenerator")
	float _timeToChangeDifficulty = 60.0f;

	UPROPERTY(EditAnywhere, Category = "LevelGenerator")
	uint8 _maxDifficultyLevel = 7;

	TQueue<AActor*> _platformQueue;

	APlayerCharacter* _playerCharacter;

	AActor* _lastPlatform;
	
	float _gameTimer;

	uint8 _difficultyIndex;
};
