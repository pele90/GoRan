// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "JumpingPlayerController.generated.h"

class UCharacterMovementComponent;
class APlayerCharacter;
class UDistanceWidget;

/**
 * 
 */
UCLASS()
class GORAN_API AJumpingPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AJumpingPlayerController();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	void SetupInputComponent() override;
	
	void Move_XAxis(float AxisValue);

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	void StartFalling();

	void StopFalling();

private:
	UPROPERTY()
	UCharacterMovementComponent* _characterMovementComponent;

	UPROPERTY()
	APlayerCharacter* _playerCharacter;

	UPROPERTY()
	UDistanceWidget* _distanceWidget;

};
