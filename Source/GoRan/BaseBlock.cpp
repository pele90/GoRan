// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBlock.h"

// Sets default values
ABaseBlock::ABaseBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseBlock::BeginPlay()
{
	Super::BeginPlay();
	
	/*_velocity = FVector(-1.0f, 0.f, 0.f);*/
}

// Called every frame
void ABaseBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*_gameTimer += DeltaTime;

	if (_gameTimer > _timeToStartIncreaseDifficultyModifier)
	{
		_bIncreasDifficultyModifier = true;
	}

	if (_bIncreasDifficultyModifier)
	{
		_horizontalSpeed += _difficultyModifierIncreaseAmount;
		_bIncreasDifficultyModifier = false;
		_gameTimer = 0.0f;
	}

	SetActorLocation(GetActorLocation() + _velocity * _horizontalSpeed);*/
}

