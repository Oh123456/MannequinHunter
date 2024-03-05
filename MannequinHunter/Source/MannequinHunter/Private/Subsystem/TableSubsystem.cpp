// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/TableSubsystem.h"
#include "Table/MannequinHunterStatusTable.h"
#include "CombatSystem/MannequinHunterCombatComponent.h"
#include "AI/AIPatternTable.h"

void UTableSubsystem::LoadAIPatternDataTable()
{

	LoadTable<FAIPatternDataTable>(TEXT("/Game/BP/DataTable/AIPatternDataTables/DT_MannequinAIPatternData.DT_MannequinAIPatternData"));
}

void UTableSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{

	LoadTable<FMannequinHunterStatusDataTable>(TEXT("/Game/BP/DataTable/DT_StatuesData.DT_StatuesData"));
	LoadTable<FCommandDataTable>(TEXT("/Game/BP/DataTable/DT_Command.DT_Command"));
	LoadTable<FAIPatternTreeTable>(TEXT("/Game/BP/DataTable/DT_AIPatternTree.DT_AIPatternTree"));

	LoadAIPatternDataTable();

}

void UTableSubsystem::Deinitialize()
{
	tableMap.Empty();
}
