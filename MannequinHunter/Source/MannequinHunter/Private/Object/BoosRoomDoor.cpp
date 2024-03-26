// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/BoosRoomDoor.h"
#include "Components/BoxComponent.h"
#include "Kismet/GamePlayStatics.h"
#include "Utility/MannequinHunterTags.h"
#include "GameMode/MannequinHunterGameMode.h"

void ABoosRoomDoor::BeginPlay()
{
	Super::BeginPlay();
	otherTrigger->OnComponentBeginOverlap.AddDynamic(this, &ABoosRoomDoor::BossMove);
}

void ABoosRoomDoor::BossMove(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag(MannequinHnterTags::PLAYER))
	{
		AMannequinHunterGameMode* gameMode = Cast<AMannequinHunterGameMode>(UGameplayStatics::GetGameMode(GetWorld()));;
		if (gameMode)
		{
			gameMode->SpawnBoos(bossName);
		}
	}
}
