// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/Door.h"
#include "Object/DoorObjectComponent.h"
#include "Components/BoxComponent.h"
#include "Utility/MannequinHunterTags.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	doorWallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorWall"));
	SetRootComponent(doorWallMesh);

	doorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	doorMesh->SetupAttachment(doorWallMesh);


	trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("DoorTrigger"));
	trigger->SetupAttachment(doorWallMesh);

	doorObjectComponent = CreateDefaultSubobject<UDoorObjectComponent>(TEXT("Door"));
	doorObjectComponent->SetDoorMesh(doorMesh);

}

void ADoor::MoveDoor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(MannequinHnterTags::PLAYER))
	{
		doorObjectComponent->CallMoveDoor();
	}
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();

	trigger->OnComponentBeginOverlap.AddDynamic(this, &ADoor::MoveDoor);
}

