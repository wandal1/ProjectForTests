// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryPickup.h"




ABatteryPickup::ABatteryPickup()
{
	bReplicateMovement = true;

	GetStaticMeshComponent()->SetSimulatePhysics(true);
	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
}
