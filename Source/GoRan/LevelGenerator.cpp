// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelGenerator.h"
#include "PlayerCharacter.h"
#include "JumpingPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "BalanceTable.h"

// Sets default values
ALevelGenerator::ALevelGenerator()
	: _difficultyIndex(0)

{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALevelGenerator::BeginPlay()
{
	Super::BeginPlay();
	
	if (AJumpingPlayerController* playerController = Cast<AJumpingPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		_playerCharacter = Cast<APlayerCharacter>(playerController->GetPawn());
	}

	UpdateDifficultyParameters();

	CreateStartPlatform();
}

// Called every frame
void ALevelGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float wantedScale = FMath::RandRange(_minPlatformSize, _maxPlatformSize);

	float distance = FVector::Dist2D(_playerCharacter->GetActorLocation(), _lastPlatform->GetActorLocation());

	if (distance < _distanceToSpawnPlatform)
	{
		FVector spawnLocation = FVector::ZeroVector;
		FRotator rotation(0.0f, 0.0f, 0.0f);
		FActorSpawnParameters spawnInfo;

		if (AActor* newPlatform = GetWorld()->SpawnActor<AActor>(_platformClass, spawnLocation, rotation, spawnInfo))
		{
			FVector platformScale = newPlatform->GetActorScale3D();
			platformScale.X = wantedScale;
			newPlatform->SetActorScale3D(platformScale);

			spawnLocation = GetNewLocation(_lastPlatform, newPlatform);
			newPlatform->SetActorLocation(spawnLocation);

			_platformQueue.Enqueue(newPlatform);

			AActor* platformToRemove = nullptr;
			if(_platformQueue.Dequeue(platformToRemove))
			{
				platformToRemove->SetLifeSpan(30.0f);
			}

			_lastPlatform = newPlatform;
		}
	}

	_gameTimer += DeltaTime;

	// if time to change difficulty
	if (_gameTimer > _timeToChangeDifficulty)
	{
		UpdateDifficultyParameters();
	}
}

void ALevelGenerator::CreateStartPlatform()
{
	FVector spawnLocation = FVector::ZeroVector;
	FRotator rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters spawnInfo;

	AActor* newPlatform = nullptr;

	newPlatform = GetWorld()->SpawnActor<AActor>(_platformClass, spawnLocation, rotation, spawnInfo);
	FVector platformScale = newPlatform->GetActorScale3D();
	platformScale.X = _maxPlatformSize;
	newPlatform->SetActorScale3D(platformScale);
	_platformQueue.Enqueue(newPlatform);
	_lastPlatform = newPlatform;

	for (int i = 0; i < 5; i++)
	{
		newPlatform = GetWorld()->SpawnActor<AActor>(_platformClass, spawnLocation, rotation, spawnInfo);

		platformScale = newPlatform->GetActorScale3D();
		platformScale.X = FMath::RandRange(_minPlatformSize, _maxPlatformSize);
		newPlatform->SetActorScale3D(platformScale);

		spawnLocation = GetNewLocation(_lastPlatform, newPlatform);
		newPlatform->SetActorLocation(spawnLocation);

		_platformQueue.Enqueue(newPlatform);

		_lastPlatform = newPlatform;
	}
}

FVector ALevelGenerator::GetNewLocation(AActor* lastPlatform, AActor* newPlatform)
{
	if (newPlatform == nullptr || lastPlatform == nullptr)
	{
		return FVector::ZeroVector;
	}

	FVector lastPlatformSize = lastPlatform->GetComponentsBoundingBox().GetSize();
	FVector newPlatformSize = newPlatform->GetComponentsBoundingBox().GetSize();

	float wantedHorizontalDistance = FMath::RandRange(_minHorizontalDistance, _maxHorizontalDistance);
	float wantedVerticalDistance = FMath::RandRange(_minVerticalDistance, _maxVerticalDistance);

	if (_maxVerticalDistance - wantedVerticalDistance < (_maxVerticalDistance / 4.0f))
	{
		wantedHorizontalDistance += _minHorizontalDistance / 3.0f;
	}

	FVector lastPlatformEdgeLocation = lastPlatform->GetActorLocation() + FVector((lastPlatformSize.X / 2.0f), 0.0f, 0.0f);
	FVector newPlatformCenterLocation = FVector(newPlatformSize.X / 2.0f, 0.0f, 0.0f);

	FVector resultLocation = lastPlatformEdgeLocation + FVector(wantedHorizontalDistance, 0.0f, wantedVerticalDistance) + newPlatformCenterLocation;

	if (resultLocation.Z < -5000.f)
	{
		resultLocation.Z += FMath::Abs(wantedVerticalDistance);
	}
	else if (resultLocation.Z > 5000.f)
	{
		resultLocation.Z -= FMath::Abs(wantedVerticalDistance);
	}

	return resultLocation;
}

void ALevelGenerator::UpdateDifficultyParameters()
{
	if (_difficultyIndex > _maxDifficultyLevel)
	{
		_difficultyIndex = _maxDifficultyLevel;
	}

	_minPlatformSize = _balanceTable->MinPlatformValues[_difficultyIndex];
	_maxPlatformSize = _balanceTable->MaxPlatformValues[_difficultyIndex];
	_minHorizontalDistance = _balanceTable->MinDistanceValues[_difficultyIndex];
	_maxHorizontalDistance = _balanceTable->MaxDistanceValues[_difficultyIndex];
	_minVerticalDistance = _balanceTable->MinHeightValues[_difficultyIndex];
	_maxVerticalDistance = _balanceTable->MaxHeightValues[_difficultyIndex];

	_difficultyIndex++;
}

