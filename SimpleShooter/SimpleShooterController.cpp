// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleShooterController.h"

#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

ASimpleShooterController::ASimpleShooterController()
	: RestartDelay(5.f)
{
}

void ASimpleShooterController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	HUD->RemoveFromViewport();

	if (bIsWinner)
	{
		UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
		if (WinScreen)
		{
			WinScreen->AddToViewport();
		}
	}
	else
	{
		UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
		if (LoseScreen)
		{
			LoseScreen->AddToViewport();
		}
	}

	GetWorldTimerManager().SetTimer(RestartTimer, this, &ASimpleShooterController::RestartLevel, RestartDelay);
}

void ASimpleShooterController::Tick(float DeltaSeconds)
{
	// 
	if (RestartTimer.IsValid())
	{
		if (GetWorldTimerManager().GetTimerElapsed(RestartTimer) <= RestartDelay)
		{
			CurrentDelayTime = CurrentDelayTime - DeltaSeconds;
			CurrentDisplayedDelayTime = CurrentDelayTime;
		}
	}
}

void ASimpleShooterController::BeginPlay()
{
	Super::BeginPlay();

	CurrentDelayTime = RestartDelay;
	//CurrentDisplayedDelayTime = RestartDelay;

	HUD = CreateWidget(this, HUDClass);
	if (HUD)
	{
		HUD->AddToViewport();
	}
}
