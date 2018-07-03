// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MP_PickUp.generated.h"

/**
 *
 */
UCLASS()
class MPTEST_API AMP_PickUp : public AStaticMeshActor
{
	GENERATED_BODY()

public:

	AMP_PickUp();

	//Required network
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	UFUNCTION(BlueprintPure, Category = "PickUp")
	bool IsActive();

	UFUNCTION(BlueprintCallable, Category = "PickUp")
		void SetActive(bool NewState);

protected:

	UPROPERTY(ReplicatedUsing = OnRep_IsActive)
		bool bIsActive;

	//This is called whenever bIsActive updated
	UFUNCTION()
	virtual void OnRep_IsActive();
};
