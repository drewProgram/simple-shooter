// Fill out your copyright notice in the Description page of Project Settings.

#include "Gun.h"

#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"

#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
	: MaxRange(1000.f), Damage(10.f), Ammo(32)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	BaseMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}

bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	AController* OwnerController = GetOwnerController();
	if (!OwnerController)
	{
		return false;
	}

	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);
	ShotDirection = -Rotation.Vector();

	FVector End = Location + Rotation.Vector() * MaxRange;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());


	return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

AController* AGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn)
	{
		return nullptr;
	}

	return OwnerPawn->GetController();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int32 AGun::GetAmmo() const
{
	return Ammo;
}

void AGun::PullTrigger()
{
	if (Ammo > 0)
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, BaseMesh, TEXT("MuzzleFlashSocket"));
		UGameplayStatics::SpawnSoundAttached(MuzzleSound, BaseMesh, TEXT("MuzzleFlashSocket"));

		FHitResult Hit;
		FVector ShotDirection;
		bool bSuccess = GunTrace(Hit, ShotDirection);
		if (bSuccess)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());
			UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ImpactSound, Hit.Location, ShotDirection.Rotation());

			AActor* HitActor = Hit.GetActor();
			if (HitActor)
			{
				FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
				AController* OwnerController = GetOwnerController();
				HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
			}
		}

		Ammo--;

		return;
	}

	if (OutOfAmmoSound)
	{
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), OutOfAmmoSound, GetActorLocation(), GetActorRotation());
		return;
	}

	UE_LOG(LogTemp, Error, TEXT("No Sound set for OutOfAmmo situation"));
}

