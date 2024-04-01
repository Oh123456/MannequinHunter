// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/NoneTriggerDoor.h"
#include "Object/DoorObjectComponent.h"

// Sets default values
ANoneTriggerDoor::ANoneTriggerDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	doorWallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorWall"));
	SetRootComponent(doorWallMesh);

	doorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	doorMesh->SetupAttachment(doorWallMesh);

	doorObjectComponent = CreateDefaultSubobject<UDoorObjectComponent>(TEXT("Door"));
	doorObjectComponent->SetDoorMesh(doorMesh);

}

void ANoneTriggerDoor::MoveDoor()
{
	doorObjectComponent->CallMoveDoor();
}
