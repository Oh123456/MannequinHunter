// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/TableSubsystem.h"
#include "Table/MannequinHunterStatusTable.h"
#include "CombatSystem/MannequinHunterCombatComponent.h"
#include "AI/AIPattern.h"

void UTableSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{

	LoadTable<FMannequinHunterStatusDataTable>(TEXT("/Game/BP/DataTable/StatuesDataTable.StatuesDataTable"));
	LoadTable<FCommandDataTable>(TEXT("/Game/BP/DataTable/CommandTable.CommandTable"));
	LoadTable<FAIPatternTable>(TEXT("/Game/BP/DataTable/AIPattenDataTable.AIPattenDataTable"));
}

void UTableSubsystem::Deinitialize()
{
	tableMap.Empty();
}
