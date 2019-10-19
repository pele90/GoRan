// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GoRanGameModeBase.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void APlayerCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (AGoRanGameModeBase* gameMode = Cast<AGoRanGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		gameMode->SetCurrentState(EGamePlayState::EGameOver);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetActorLocation().Z < -5000.0f)
	{
		Destroy();
	}

}

