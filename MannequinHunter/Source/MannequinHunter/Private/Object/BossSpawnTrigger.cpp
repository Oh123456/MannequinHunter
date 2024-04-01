// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/BossSpawnTrigger.h"
#include "GameMode/MannequinHunterGameMode.h"
#include "Object/NoneTriggerDoor.h"

ABossSpawnTrigger::ABossSpawnTrigger()
{
	spawnData.isBoss = true;
}

void ABossSpawnTrigger::SpawnMonster(AMannequinHunterGameMode* gameMode)
{
	Super::SpawnMonster(gameMode);


	gameMode->OnClearBossEvent.AddLambda([this] (class ABaseActionCharacter* boss)
		{
			for (ANoneTriggerDoor* door : bossClearDoors)
			{
				if (door)
					door->MoveDoor();
			}
		});

}

