// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GoRanGameModeBase.generated.h"

//enum to store the current state of gameplay
UENUM()
enum class EGamePlayState
{
	EPlaying,
	EGameOver,
	EUnknown
};

/**
 * 
 */
UCLASS()
class GORAN_API AGoRanGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AGoRanGameModeBase();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	/** Returns the current playing state */
	UFUNCTION(BlueprintPure, Category = "GameMode")
	EGamePlayState GetCurrentState() const;

	/** Sets a new playing state */
	void SetCurrentState(EGamePlayState NewState);

private:
	/**Keeps track of the current playing state */
	EGamePlayState CurrentState;

	/**Handle any function calls that rely upon changing the playing state of our game */
	void HandleNewState(EGamePlayState NewState);
};
