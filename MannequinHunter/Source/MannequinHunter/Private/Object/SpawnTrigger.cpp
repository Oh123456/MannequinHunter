// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/SpawnTrigger.h"
#include "Components/BoxComponent.h"
#include "Kismet/GamePlayStatics.h"
#include "Utility/MannequinHunterTags.h"
#include "GameMode/MannequinHunterGameMode.h"
#include "Object/SpawnPoint.h"

// Sets default values
ASpawnTrigger::ASpawnTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	triggerComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	SetRootComponent(triggerComponent);
}

// Called when the game starts or when spawned
void ASpawnTrigger::BeginPlay()
{
	Super::BeginPlay();
	

	triggerComponent->OnComponentBeginOverlap.AddDynamic(this, &ASpawnTrigger::Spawn);
}

void ASpawnTrigger::Spawn(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag(MannequinHnterTags::PLAYER))
	{
		AMannequinHunterGameMode* gameMode = Cast<AMannequinHunterGameMode>(UGameplayStatics::GetGameMode(GetWorld()));;
		if (gameMode)
		{
			gameMode->SpawnMonster(spawnData.spawnName, spawnData.spawnPoint->GetActorTransform(), spawnData.isBoss);
			// 액터를 감춤 
			SetActorHiddenInGame(true);
			// 충돌 계산 비활성화
			SetActorEnableCollision(false);
		}
	}
}

