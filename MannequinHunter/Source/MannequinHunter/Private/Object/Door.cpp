// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/Door.h"
#include "Components/BoxComponent.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	doorWallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorWall"));
	SetRootComponent(doorWallMesh);

	doorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	doorMesh->SetupAttachment(doorWallMesh);

	trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("DoorTrigger"));
	trigger->SetupAttachment(doorWallMesh);

}

