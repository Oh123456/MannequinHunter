// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/TableSubsystem.h"
#include "Table/MannequinHunterStatusTable.h"
#include "CombatSystem/MannequinHunterCombatComponent.h"
#include "AI/AIPatternTable.h"
#include "Table/SpawnTable.h"

const TCHAR* AIPatternPath = TEXT("/Game/BP/DataTable/AIPatternDataTables/");

const UDataTable* UTableSubsystem::LoadAIPatternTable(const FName& tableName)
{
	FString path = AIPatternPath;
	path.Append(tableName.ToString());
	return LoadObject<UDataTable>(nullptr, (*path));
}

void UTableSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{

	LoadTable<FMannequinHunterStatusDataTable>(TEXT("/Game/BP/DataTable/DT_StatuesData"));
	LoadTable<FCommandDataTable>(TEXT("/Game/BP/DataTable/DT_Command"));
	LoadTable<FAIPatternTreeTable>(TEXT("/Game/BP/DataTable/DT_AIPatternTree"));
	LoadTable<FSpawnDataTable>(TEXT("/Game/BP/DataTable/DT_SpawnTable.DT_SpawnTable"));
	///Script/Engine.DataTable'/Game/BP/DataTable/DT_SpawnTable.DT_SpawnTable'


}

void UTableSubsystem::Deinitialize()
{
	tableMap.Empty();
}
