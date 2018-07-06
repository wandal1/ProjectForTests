// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MP_SpawnVolume.generated.h"

UCLASS()
class MPTEST_API AMP_SpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMP_SpawnVolume();

	FORCEINLINE class UBoxComponent* GetSpawnVolume() const { return SpawnVolume;  }

	UFUNCTION(BlueprintPure, Category = "Spawning")
	FVector GetRandomPointInVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawn", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent *SpawnVolume;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AMP_PickUp> WhatToSpawn;

	FTimerHandle Spawn_TH;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SpawnTime_Min = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SpawnTime_Max = 4.5;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnPick();

	float SpawnDelay;
	
};
