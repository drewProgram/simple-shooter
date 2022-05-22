// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SimpleShooterController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API ASimpleShooterController : public APlayerController
{
	GENERATED_BODY()

public:
	ASimpleShooterController();

	UPROPERTY(BlueprintReadOnly)
	int32 CurrentDisplayedDelayTime;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LoseScreenClass;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> WinScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUDClass;

	UPROPERTY()
	UUserWidget* HUD;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float RestartDelay;

	float CurrentDelayTime;

	FTimerHandle RestartTimer;
	
public:
	virtual void Tick(float DeltaSeconds) override;

	virtual void GameHasEnded(AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

protected:
	virtual void BeginPlay() override;
};
