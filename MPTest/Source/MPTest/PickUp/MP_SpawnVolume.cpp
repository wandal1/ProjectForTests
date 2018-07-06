// Fill out your copyright notice in the Description page of Project Settings.

#include "MP_SpawnVolume.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "MP_PickUp.h"


// Sets default values
AMP_SpawnVolume::AMP_SpawnVolume()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	if (Role == ROLE_Authority)
	{
		SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawnvolume"));
		SetRootComponent(Cast<USceneComponent>(SpawnVolume));
	}

}

FVector AMP_SpawnVolume::GetRandomPointInVolume()
{
	if (!SpawnVolume)
		return FVector();

	FVector SpawnOrigin = SpawnVolume->Bounds.Origin;
	FVector SpawnExtent = SpawnVolume->Bounds.BoxExtent;
	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);

}

// Called when the game starts or when spawned
void AMP_SpawnVolume::BeginPlay()
{
	Super::BeginPlay();

	SpawnDelay = FMath::FRandRange(SpawnTime_Min, SpawnTime_Max);
	GetWorld()->GetTimerManager().SetTimer(Spawn_TH, this, &AMP_SpawnVolume::SpawnPick, SpawnDelay, false);

}

// Called every frame
void AMP_SpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMP_SpawnVolume::SpawnPick()
{
	//if we are the server and have smthing to spawn
	if (Role == ROLE_Authority && WhatToSpawn)
	{
		if (UWorld*  const World = GetWorld())
		{

			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			FVector SpawnLoc = GetRandomPointInVolume();
			FRotator SpawnRot;
			SpawnRot.Yaw = FMath::Rand() * 360;
			SpawnRot.Pitch = FMath::Rand() * 360;
			SpawnRot.Roll = FMath::Rand() * 360;

			AMP_PickUp* const SpawnedPickup = GetWorld()->SpawnActor<AMP_PickUp>(WhatToSpawn, SpawnLoc, SpawnRot,  SpawnParams);

			SpawnDelay = FMath::FRandRange(SpawnTime_Min, SpawnTime_Max);
			GetWorld()->GetTimerManager().SetTimer(Spawn_TH, this, &AMP_SpawnVolume::SpawnPick, SpawnDelay, false);

		}
	}
}

