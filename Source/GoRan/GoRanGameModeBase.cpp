// Fill out your copyright notice in the Description page of Project Settings.


#include "GoRanGameModeBase.h"
#include "Kismet/GameplayStatics.h"

AGoRanGameModeBase::AGoRanGameModeBase()
	: Super()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGoRanGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	SetCurrentState(EGamePlayState::EPlaying);
}

void AGoRanGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GetWorld()->GetMapName();
}

EGamePlayState AGoRanGameModeBase::GetCurrentState() const
{
	return CurrentState;
}

void AGoRanGameModeBase::SetCurrentState(EGamePlayState NewState)
{
	if (CurrentState == NewState) 
	{
		return;
	}

	CurrentState = NewState;
	HandleNewState(CurrentState);
}

void AGoRanGameModeBase::HandleNewState(EGamePlayState NewState)
{
	switch (NewState)
	{
	case EGamePlayState::EPlaying:
	{
		// do nothing
	}
	break;
	// Unknown/default state
	case EGamePlayState::EGameOver:
	{
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	}
	break;
	// Unknown/default state
	default:
	case EGamePlayState::EUnknown:
	{
		// do nothing
	}
	break;
	}
}
