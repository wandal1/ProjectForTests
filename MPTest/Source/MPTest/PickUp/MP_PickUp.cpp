// Fill out your copyright notice in the Description page of Project Settings.

#include "MP_PickUp.h"
#include "Net/UnrealNetwork.h"



AMP_PickUp::AMP_PickUp()
{
	//Tell engine to replicate this actor
	bReplicates = true;

	//Pickups do not need to tick
	PrimaryActorTick.bCanEverTick = false;

	SetActive(true);
}

void AMP_PickUp::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMP_PickUp, bIsActive);
}

bool AMP_PickUp::IsActive()
{
	return bIsActive;
}

void AMP_PickUp::SetActive(bool NewState)
{
	if (Role = ROLE_Authority)
	{
		bIsActive = NewState;
	}

}

void AMP_PickUp::OnRep_IsActive()
{

}
