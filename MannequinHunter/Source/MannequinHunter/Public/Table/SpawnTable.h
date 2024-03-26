// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SpawnTable.generated.h"

/**
 * 
 */

USTRUCT(Blueprinttype)
struct FSpawnDataTable : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AActor> spawnActor;
};

UCLASS()
class MANNEQUINHUNTER_API USpawnTable : public UDataTable
{
	GENERATED_BODY()
	
};
