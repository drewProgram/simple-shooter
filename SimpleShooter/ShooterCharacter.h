// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(Category = "Camera", VisibleAnywhere)
	class UCameraComponent* Camera;
	UPROPERTY(Category = "Camera", VisibleAnywhere)
	class USpringArmComponent* SpringArm;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;
	UPROPERTY()
	AGun* Gun;

	UPROPERTY(EditAnywhere)
	float RotationRate;
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth;

	UPROPERTY(VisibleAnywhere)
	float Health;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure)
	bool CheckIsAlive() const;
	
	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	UFUNCTION(BlueprintPure)
	int32 GetAmmo() const;
	
	void Shoot();

private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);

};
