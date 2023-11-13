// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/Equipment.h"

// Sets default values
AEquipment::AEquipment(EEquipmentType type) : Super(),
equipmentType(type)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}
