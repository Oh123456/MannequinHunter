// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/TwoTriggerDoor.h"
#include "Components/BoxComponent.h"

ATwoTriggerDoor::ATwoTriggerDoor() : Super()
{
	otherTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("DoorOtherTrigger"));
	otherTrigger->SetupAttachment(doorWallMesh);
	
}
