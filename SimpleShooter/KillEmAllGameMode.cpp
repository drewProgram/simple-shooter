// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"

#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"

void AKillEmAllGameMode::SetPawnKilled(APawn* PawnKilled)
{
	Super::SetPawnKilled(PawnKilled);

	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController)
	{
		EndGame(false);
	}

	for (AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld()))
	{
		if (!Controller->CheckIsDead())
		{
			return;
		}
	}

	EndGame(true);
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}
