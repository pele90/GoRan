// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpingPlayerController.h"
#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DistanceWidget.h"
#include "GameHUD.h"
#include "Components/InputComponent.h"

AJumpingPlayerController::AJumpingPlayerController()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AJumpingPlayerController::BeginPlay()
{
	Super::BeginPlay();

	_playerCharacter = Cast<APlayerCharacter>(GetPawn());
	if (_playerCharacter == nullptr)
	{
		return;
	}

	_characterMovementComponent = Cast<UCharacterMovementComponent>(_playerCharacter->GetMovementComponent());
}

void AJumpingPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(_characterMovementComponent == nullptr)
	{
		return;
	}

	if (_characterMovementComponent->MovementMode != MOVE_Falling)
	{
		if (_playerCharacter != nullptr)
		{
			_playerCharacter->Jump();
		}
	}

	if (_distanceWidget == nullptr)
	{
		if (AGameHUD* gameHUD = Cast<AGameHUD>(GetHUD()))
		{
			_distanceWidget = gameHUD->GetDistanceWidget();

			if (_distanceWidget != nullptr)
			{
				_distanceWidget->UpdateDistance(_playerCharacter->GetActorLocation().X);
			}
		}
	}

	if (_characterMovementComponent->Velocity.X > 0.0f)
	{
		if (_distanceWidget != nullptr)
		{
			_distanceWidget->UpdateDistance(_playerCharacter->GetActorLocation().X);
		}
	}

	_playerCharacter->AddMovementInput(FVector(1.0f, 0.f, 0.f));
}

void AJumpingPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveX", this, &AJumpingPlayerController::Move_XAxis);

	InputComponent->BindTouch(IE_Pressed, this, &AJumpingPlayerController::TouchStarted);
	InputComponent->BindTouch(IE_Released, this, &AJumpingPlayerController::TouchStopped);
}

void AJumpingPlayerController::Move_XAxis(float AxisValue)
{
	if (_playerCharacter != nullptr)
	{
		if (AxisValue > 0.0f)
		{
			StopFalling();
		}
		else
		{
			StartFalling();
		}
	}
}

void AJumpingPlayerController::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopFalling();
}

void AJumpingPlayerController::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StartFalling();
}

void AJumpingPlayerController::StartFalling()
{
	_playerCharacter->StopJumping();
	_characterMovementComponent->GravityScale = 4.0f;
}

void AJumpingPlayerController::StopFalling()
{
	_characterMovementComponent->GravityScale = 1.0f;
}
