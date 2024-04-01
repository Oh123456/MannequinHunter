// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/SpawnTrigger.h"
#include "BossSpawnTrigger.generated.h"

/**
 * 
 */
UCLASS()
class MANNEQUINHUNTER_API ABossSpawnTrigger : public ASpawnTrigger
{
	GENERATED_BODY()
	
public:
	ABossSpawnTrigger();

protected:

	virtual void SpawnMonster(class AMannequinHunterGameMode* gameMode) override;
protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	TArray<class ANoneTriggerDoor*> bossClearDoors;
};
