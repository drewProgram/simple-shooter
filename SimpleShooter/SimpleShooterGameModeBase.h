// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SimpleShooterGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API ASimpleShooterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Menu")
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	virtual void SetPawnKilled(APawn* PawnKilled);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menu")
	TSubclassOf<UUserWidget> StartingWidgetClass;

	UPROPERTY()
	UUserWidget* CurrentWidget;
};
